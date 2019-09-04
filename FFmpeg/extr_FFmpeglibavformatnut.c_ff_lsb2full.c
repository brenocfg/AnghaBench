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
struct TYPE_3__ {unsigned long long msb_pts_shift; int last_pts; } ;
typedef  TYPE_1__ StreamContext ;

/* Variables and functions */

int64_t ff_lsb2full(StreamContext *stream, int64_t lsb)
{
    int64_t mask  = (1ULL << stream->msb_pts_shift) - 1;
    int64_t delta = stream->last_pts - mask / 2;
    return ((lsb - delta) & mask) + delta;
}