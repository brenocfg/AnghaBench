#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_3__ {unsigned int timeres; int shift; } ;
typedef  TYPE_1__ JACOsubContext ;

/* Variables and functions */
 int sscanf (char const*,char*,...) ; 

__attribute__((used)) static const char *read_ts(JACOsubContext *jacosub, const char *buf,
                           int64_t *start, int64_t *duration)
{
    int len;
    unsigned hs, ms, ss, fs; // hours, minutes, seconds, frame start
    unsigned he, me, se, fe; // hours, minutes, seconds, frame end
    int ts_start, ts_end;
    int64_t ts_start64, ts_end64;

    /* timed format */
    if (sscanf(buf, "%u:%u:%u.%u %u:%u:%u.%u %n",
               &hs, &ms, &ss, &fs,
               &he, &me, &se, &fe, &len) == 8) {
        ts_start = (hs*3600 + ms*60 + ss) * jacosub->timeres + fs;
        ts_end   = (he*3600 + me*60 + se) * jacosub->timeres + fe;
        goto shift_and_ret;
    }

    /* timestamps format */
    if (sscanf(buf, "@%u @%u %n", &ts_start, &ts_end, &len) == 2)
        goto shift_and_ret;

    return NULL;

shift_and_ret:
    ts_start64  = (ts_start + jacosub->shift) * 100LL / jacosub->timeres;
    ts_end64    = (ts_end   + jacosub->shift) * 100LL / jacosub->timeres;
    *start    = ts_start64;
    *duration = ts_end64 - ts_start64;
    return buf + len;
}