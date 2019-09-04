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
typedef  void* uint32_t ;
typedef  void* int32_t ;
struct TYPE_3__ {int jitter; void* transit; } ;
typedef  TYPE_1__ RTPStatistics ;

/* Variables and functions */
 void* FFABS (void*) ; 

__attribute__((used)) static void rtcp_update_jitter(RTPStatistics *s, uint32_t sent_timestamp,
                               uint32_t arrival_timestamp)
{
    // Most of this is pretty straight from RFC 3550 appendix A.8
    uint32_t transit = arrival_timestamp - sent_timestamp;
    uint32_t prev_transit = s->transit;
    int32_t d = transit - prev_transit;
    // Doing the FFABS() call directly on the "transit - prev_transit"
    // expression doesn't work, since it's an unsigned expression. Doing the
    // transit calculation in unsigned is desired though, since it most
    // probably will need to wrap around.
    d = FFABS(d);
    s->transit = transit;
    if (!prev_transit)
        return;
    s->jitter += d - (int32_t) ((s->jitter + 8) >> 4);
}