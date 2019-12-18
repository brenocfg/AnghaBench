#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ctb_row ;
struct TYPE_22__ {TYPE_6__* priv_data; } ;
struct TYPE_19__ {TYPE_3__* sps; TYPE_2__* pps; } ;
struct TYPE_16__ {int slice_ctb_addr_rs; int num_entry_point_offsets; int /*<<< orphan*/ * size; scalar_t__* offset; } ;
struct TYPE_21__ {int threads_number; int* tab_slice_address; int /*<<< orphan*/  avctx; int /*<<< orphan*/  wpp_err; TYPE_4__ ps; TYPE_1__ sh; scalar_t__ data; TYPE_5__* HEVClc; struct TYPE_21__** sList; } ;
struct TYPE_20__ {int /*<<< orphan*/  cc; int /*<<< orphan*/  gb; } ;
struct TYPE_18__ {int log2_ctb_size; int width; int ctb_size; int ctb_width; int height; } ;
struct TYPE_17__ {int* ctb_addr_rs_to_ts; int* ctb_addr_ts_to_rs; } ;
typedef  TYPE_5__ HEVCLocalContext ;
typedef  TYPE_6__ HEVCContext ;
typedef  TYPE_7__ AVCodecContext ;

/* Variables and functions */
 int SHIFT_CTB_WPP ; 
 scalar_t__ atomic_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_store (int /*<<< orphan*/ *,int) ; 
 int ff_hevc_cabac_init (TYPE_6__*,int) ; 
 int /*<<< orphan*/  ff_hevc_hls_filter (TYPE_6__*,int,int,int) ; 
 int /*<<< orphan*/  ff_hevc_hls_filters (TYPE_6__*,int,int,int) ; 
 int /*<<< orphan*/  ff_hevc_save_states (TYPE_6__*,int) ; 
 int /*<<< orphan*/  ff_init_cabac_decoder (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_thread_await_progress2 (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  ff_thread_report_progress2 (int /*<<< orphan*/ ,int,int,int) ; 
 int hls_coding_quadtree (TYPE_6__*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hls_decode_neighbour (TYPE_6__*,int,int,int) ; 
 int /*<<< orphan*/  hls_sao_param (TYPE_6__*,int,int) ; 
 int init_get_bits8 (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hls_decode_entry_wpp(AVCodecContext *avctxt, void *input_ctb_row, int job, int self_id)
{
    HEVCContext *s1  = avctxt->priv_data, *s;
    HEVCLocalContext *lc;
    int ctb_size    = 1<< s1->ps.sps->log2_ctb_size;
    int more_data   = 1;
    int *ctb_row_p    = input_ctb_row;
    int ctb_row = ctb_row_p[job];
    int ctb_addr_rs = s1->sh.slice_ctb_addr_rs + ctb_row * ((s1->ps.sps->width + ctb_size - 1) >> s1->ps.sps->log2_ctb_size);
    int ctb_addr_ts = s1->ps.pps->ctb_addr_rs_to_ts[ctb_addr_rs];
    int thread = ctb_row % s1->threads_number;
    int ret;

    s = s1->sList[self_id];
    lc = s->HEVClc;

    if(ctb_row) {
        ret = init_get_bits8(&lc->gb, s->data + s->sh.offset[ctb_row - 1], s->sh.size[ctb_row - 1]);
        if (ret < 0)
            goto error;
        ff_init_cabac_decoder(&lc->cc, s->data + s->sh.offset[(ctb_row)-1], s->sh.size[ctb_row - 1]);
    }

    while(more_data && ctb_addr_ts < s->ps.sps->ctb_size) {
        int x_ctb = (ctb_addr_rs % s->ps.sps->ctb_width) << s->ps.sps->log2_ctb_size;
        int y_ctb = (ctb_addr_rs / s->ps.sps->ctb_width) << s->ps.sps->log2_ctb_size;

        hls_decode_neighbour(s, x_ctb, y_ctb, ctb_addr_ts);

        ff_thread_await_progress2(s->avctx, ctb_row, thread, SHIFT_CTB_WPP);

        if (atomic_load(&s1->wpp_err)) {
            ff_thread_report_progress2(s->avctx, ctb_row , thread, SHIFT_CTB_WPP);
            return 0;
        }

        ret = ff_hevc_cabac_init(s, ctb_addr_ts);
        if (ret < 0)
            goto error;
        hls_sao_param(s, x_ctb >> s->ps.sps->log2_ctb_size, y_ctb >> s->ps.sps->log2_ctb_size);
        more_data = hls_coding_quadtree(s, x_ctb, y_ctb, s->ps.sps->log2_ctb_size, 0);

        if (more_data < 0) {
            ret = more_data;
            goto error;
        }

        ctb_addr_ts++;

        ff_hevc_save_states(s, ctb_addr_ts);
        ff_thread_report_progress2(s->avctx, ctb_row, thread, 1);
        ff_hevc_hls_filters(s, x_ctb, y_ctb, ctb_size);

        if (!more_data && (x_ctb+ctb_size) < s->ps.sps->width && ctb_row != s->sh.num_entry_point_offsets) {
            atomic_store(&s1->wpp_err, 1);
            ff_thread_report_progress2(s->avctx, ctb_row ,thread, SHIFT_CTB_WPP);
            return 0;
        }

        if ((x_ctb+ctb_size) >= s->ps.sps->width && (y_ctb+ctb_size) >= s->ps.sps->height ) {
            ff_hevc_hls_filter(s, x_ctb, y_ctb, ctb_size);
            ff_thread_report_progress2(s->avctx, ctb_row , thread, SHIFT_CTB_WPP);
            return ctb_addr_ts;
        }
        ctb_addr_rs       = s->ps.pps->ctb_addr_ts_to_rs[ctb_addr_ts];
        x_ctb+=ctb_size;

        if(x_ctb >= s->ps.sps->width) {
            break;
        }
    }
    ff_thread_report_progress2(s->avctx, ctb_row ,thread, SHIFT_CTB_WPP);

    return 0;
error:
    s->tab_slice_address[ctb_addr_rs] = -1;
    atomic_store(&s1->wpp_err, 1);
    ff_thread_report_progress2(s->avctx, ctb_row ,thread, SHIFT_CTB_WPP);
    return ret;
}