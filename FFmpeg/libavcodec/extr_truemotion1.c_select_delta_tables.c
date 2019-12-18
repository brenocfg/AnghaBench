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
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_3__ {int* ydt; int* cdt; int* fat_ydt; int* fat_cdt; } ;
typedef  TYPE_1__ TrueMotion1Context ;

/* Variables and functions */
 int /*<<< orphan*/ * cdts ; 
 int /*<<< orphan*/ * fat_cdts ; 
 int /*<<< orphan*/ * fat_ydts ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * ydts ; 

__attribute__((used)) static void select_delta_tables(TrueMotion1Context *s, int delta_table_index)
{
    int i;

    if (delta_table_index > 3)
        return;

    memcpy(s->ydt, ydts[delta_table_index], 8 * sizeof(int16_t));
    memcpy(s->cdt, cdts[delta_table_index], 8 * sizeof(int16_t));
    memcpy(s->fat_ydt, fat_ydts[delta_table_index], 8 * sizeof(int16_t));
    memcpy(s->fat_cdt, fat_cdts[delta_table_index], 8 * sizeof(int16_t));

    /* Y skinny deltas need to be halved for some reason; maybe the
     * skinny Y deltas should be modified */
    for (i = 0; i < 8; i++)
    {
        /* drop the lsb before dividing by 2-- net effect: round down
         * when dividing a negative number (e.g., -3/2 = -2, not -1) */
        s->ydt[i] &= 0xFFFE;
        s->ydt[i] /= 2;
    }
}