#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  avctx; TYPE_1__* envelope_quant_index; int /*<<< orphan*/  gb; } ;
struct TYPE_7__ {int total_subbands; int js_subband_start; } ;
struct TYPE_6__ {int /*<<< orphan*/  bits; int /*<<< orphan*/  table; } ;
typedef  TYPE_2__ COOKSubpacket ;
typedef  TYPE_3__ COOKContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int decode_envelope(COOKContext *q, COOKSubpacket *p,
                           int *quant_index_table)
{
    int i, j, vlc_index;

    quant_index_table[0] = get_bits(&q->gb, 6) - 6; // This is used later in categorize

    for (i = 1; i < p->total_subbands; i++) {
        vlc_index = i;
        if (i >= p->js_subband_start * 2) {
            vlc_index -= p->js_subband_start;
        } else {
            vlc_index /= 2;
            if (vlc_index < 1)
                vlc_index = 1;
        }
        if (vlc_index > 13)
            vlc_index = 13; // the VLC tables >13 are identical to No. 13

        j = get_vlc2(&q->gb, q->envelope_quant_index[vlc_index - 1].table,
                     q->envelope_quant_index[vlc_index - 1].bits, 2);
        quant_index_table[i] = quant_index_table[i - 1] + j - 12; // differential encoding
        if (quant_index_table[i] > 63 || quant_index_table[i] < -63) {
            av_log(q->avctx, AV_LOG_ERROR,
                   "Invalid quantizer %d at position %d, outside [-63, 63] range\n",
                   quant_index_table[i], i);
            return AVERROR_INVALIDDATA;
        }
    }

    return 0;
}