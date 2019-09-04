#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ lsb_bits; } ;
typedef  TYPE_1__ BestOffset ;

/* Variables and functions */

__attribute__((used)) static int compare_best_offset(BestOffset *prev, BestOffset *cur)
{
    if (prev->lsb_bits != cur->lsb_bits)
        return 1;

    return 0;
}