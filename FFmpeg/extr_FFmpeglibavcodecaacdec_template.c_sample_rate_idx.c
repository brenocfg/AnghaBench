#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */

__attribute__((used)) static int sample_rate_idx (int rate)
{
         if (92017 <= rate) return 0;
    else if (75132 <= rate) return 1;
    else if (55426 <= rate) return 2;
    else if (46009 <= rate) return 3;
    else if (37566 <= rate) return 4;
    else if (27713 <= rate) return 5;
    else if (23004 <= rate) return 6;
    else if (18783 <= rate) return 7;
    else if (13856 <= rate) return 8;
    else if (11502 <= rate) return 9;
    else if (9391  <= rate) return 10;
    else                    return 11;
}