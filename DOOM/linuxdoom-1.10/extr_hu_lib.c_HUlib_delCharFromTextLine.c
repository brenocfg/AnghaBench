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
struct TYPE_3__ {size_t len; int needsupdate; scalar_t__* l; } ;
typedef  TYPE_1__ hu_textline_t ;
typedef  int boolean ;

/* Variables and functions */

boolean HUlib_delCharFromTextLine(hu_textline_t* t)
{

    if (!t->len) return false;
    else
    {
	t->l[--t->len] = 0;
	t->needsupdate = 4;
	return true;
    }

}