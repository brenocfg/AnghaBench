#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_9__ {int /*<<< orphan*/  pb; TYPE_1__* priv_data; } ;
struct TYPE_8__ {int pts; int size; int* data; } ;
struct TYPE_7__ {int inside; int prev_h; int prev_m; int prev_s; int prev_f; scalar_t__ n; } ;
typedef  TYPE_1__ SCCContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avio_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int scc_write_packet(AVFormatContext *avf, AVPacket *pkt)
{
    SCCContext *scc = avf->priv_data;
    int64_t pts = pkt->pts;
    int i, h, m, s, f;

    if (pts == AV_NOPTS_VALUE) {
        av_log(avf, AV_LOG_WARNING,
               "Insufficient timestamps.\n");
        return 0;
    }

    h = (int)(pts / (3600000));
    m = (int)(pts / (60000)) % 60;
    s = (int)(pts /  1000) % 60;
    f = (int)(pts %  1000) / 33;

    for (i = 0; i < pkt->size; i+=3) {
        if (pkt->data[i] == 0xfc && ((pkt->data[i + 1] != 0x80 || pkt->data[i + 2] != 0x80)))
            break;
    }
    if (i >= pkt->size)
        return 0;

    if (!scc->inside && (scc->prev_h != h || scc->prev_m != m || scc->prev_s != s || scc->prev_f != f)) {
        avio_printf(avf->pb, "\n%02d:%02d:%02d:%02d\t", h, m, s, f);
        scc->inside = 1;
    }
    for (i = 0; i < pkt->size; i+=3) {
        if (i + 3 > pkt->size)
            break;

        if (pkt->data[i] != 0xfc || (pkt->data[i + 1] == 0x80 && pkt->data[i + 2] == 0x80))
            continue;
        if (!scc->inside) {
            avio_printf(avf->pb, "\n%02d:%02d:%02d:%02d\t", h, m, s, f);
            scc->inside = 1;
        }
        if (scc->n > 0)
            avio_printf(avf->pb, " ");
        avio_printf(avf->pb, "%02x%02x", pkt->data[i + 1], pkt->data[i + 2]);
        scc->n++;
    }
    if (scc->inside && (scc->prev_h != h || scc->prev_m != m || scc->prev_s != s || scc->prev_f != f)) {
        avio_printf(avf->pb, "\n");
        scc->n = 0;
        scc->inside = 0;
    }

    scc->prev_h = h;
    scc->prev_m = m;
    scc->prev_s = s;
    scc->prev_f = f;
    return 0;
}