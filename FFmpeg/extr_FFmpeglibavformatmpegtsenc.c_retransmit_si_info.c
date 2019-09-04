#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_8__ {TYPE_1__* priv_data; } ;
struct TYPE_7__ {scalar_t__ sdt_packet_count; scalar_t__ sdt_packet_period; scalar_t__ last_sdt_ts; double sdt_period; scalar_t__ pat_packet_count; scalar_t__ pat_packet_period; scalar_t__ last_pat_ts; double pat_period; int nb_services; int /*<<< orphan*/ * services; } ;
typedef  TYPE_1__ MpegTSWrite ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 void* FFMAX (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mpegts_write_pat (TYPE_2__*) ; 
 int /*<<< orphan*/  mpegts_write_pmt (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpegts_write_sdt (TYPE_2__*) ; 

__attribute__((used)) static void retransmit_si_info(AVFormatContext *s, int force_pat, int64_t dts)
{
    MpegTSWrite *ts = s->priv_data;
    int i;

    if (++ts->sdt_packet_count == ts->sdt_packet_period ||
        (dts != AV_NOPTS_VALUE && ts->last_sdt_ts == AV_NOPTS_VALUE) ||
        (dts != AV_NOPTS_VALUE && dts - ts->last_sdt_ts >= ts->sdt_period*90000.0)
    ) {
        ts->sdt_packet_count = 0;
        if (dts != AV_NOPTS_VALUE)
            ts->last_sdt_ts = FFMAX(dts, ts->last_sdt_ts);
        mpegts_write_sdt(s);
    }
    if (++ts->pat_packet_count == ts->pat_packet_period ||
        (dts != AV_NOPTS_VALUE && ts->last_pat_ts == AV_NOPTS_VALUE) ||
        (dts != AV_NOPTS_VALUE && dts - ts->last_pat_ts >= ts->pat_period*90000.0) ||
        force_pat) {
        ts->pat_packet_count = 0;
        if (dts != AV_NOPTS_VALUE)
            ts->last_pat_ts = FFMAX(dts, ts->last_pat_ts);
        mpegts_write_pat(s);
        for (i = 0; i < ts->nb_services; i++)
            mpegts_write_pmt(s, ts->services[i]);
    }
}