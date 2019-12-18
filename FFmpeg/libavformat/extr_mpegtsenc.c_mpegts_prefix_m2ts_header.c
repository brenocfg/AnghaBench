#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  tp_extra_header ;
typedef  int int64_t ;
struct TYPE_6__ {int /*<<< orphan*/  pb; TYPE_1__* priv_data; } ;
struct TYPE_5__ {scalar_t__ m2ts_mode; } ;
typedef  TYPE_1__ MpegTSWrite ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AV_RB32 (int*) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int get_pcr (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mpegts_prefix_m2ts_header(AVFormatContext *s)
{
    MpegTSWrite *ts = s->priv_data;
    if (ts->m2ts_mode) {
        int64_t pcr = get_pcr(s->priv_data, s->pb);
        uint32_t tp_extra_header = pcr % 0x3fffffff;
        tp_extra_header = AV_RB32(&tp_extra_header);
        avio_write(s->pb, (unsigned char *) &tp_extra_header,
                   sizeof(tp_extra_header));
    }
}