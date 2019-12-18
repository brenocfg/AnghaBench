#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ number; } ;
typedef  TYPE_1__ joy_elemdata_t ;

/* Variables and functions */

__attribute__((used)) static int joy_cmp_buttons(const void *e1, const void *e2)  {
    const joy_elemdata_t *b1 = (const joy_elemdata_t *)e1;
    const joy_elemdata_t *b2 = (const joy_elemdata_t *)e2;
    
    return b1->number < b2->number ? -1 :
        (b1->number > b2->number ? 1 : 0);
}