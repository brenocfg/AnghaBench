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
struct TYPE_3__ {int intra_dc_threshold; } ;
typedef  TYPE_1__ Mpeg4DecContext ;

/* Variables and functions */

__attribute__((used)) static int mpeg4_get_intra_dc_vlc_thr(Mpeg4DecContext *s)
{
    switch (s->intra_dc_threshold) {
    case 99: return 0;
    case 13: return 1;
    case 15: return 2;
    case 17: return 3;
    case 19: return 4;
    case 21: return 5;
    case 23: return 6;
    case 0:  return 7;
    }
    return 0;
}