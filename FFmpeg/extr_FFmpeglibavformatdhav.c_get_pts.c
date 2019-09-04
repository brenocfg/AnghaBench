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
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_8__ {TYPE_2__* priv_data; } ;
struct TYPE_7__ {scalar_t__ timestamp; } ;
struct TYPE_6__ {scalar_t__ last_timestamp; int /*<<< orphan*/  pts; } ;
typedef  TYPE_1__ DHAVStream ;
typedef  TYPE_2__ DHAVContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 

__attribute__((used)) static int64_t get_pts(AVFormatContext *s, DHAVStream *st)
{
    DHAVContext *dhav = s->priv_data;
    /*
    int year, month, day, hour, min, sec;
    struct tm timeinfo;

    sec   =   dhav->date        & 0x3F;
    min   =  (dhav->date >>  6) & 0x3F;
    hour  =  (dhav->date >> 12) & 0x1F;
    day   =  (dhav->date >> 17) & 0x1F;
    month =  (dhav->date >> 22) & 0x0F;
    year  = ((dhav->date >> 26) & 0x3F) + 2000;

    timeinfo.tm_year = year - 1900;
    timeinfo.tm_mon  = month - 1;
    timeinfo.tm_mday = day;
    timeinfo.tm_hour = hour;
    timeinfo.tm_min  = min;
    timeinfo.tm_sec  = sec;*/

    if (st->last_timestamp == AV_NOPTS_VALUE) {
        st->last_timestamp = dhav->timestamp;
    }

    if (st->last_timestamp <= dhav->timestamp) {
        st->pts += dhav->timestamp - st->last_timestamp;
    } else {
        st->pts += 65535 + dhav->timestamp - st->last_timestamp;
    }

    st->last_timestamp = dhav->timestamp;

    return st->pts;
}