#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int h; scalar_t__* on; scalar_t__ laston; TYPE_2__* l; } ;
typedef  TYPE_1__ hu_stext_t ;
struct TYPE_5__ {int needsupdate; } ;

/* Variables and functions */
 int /*<<< orphan*/  HUlib_eraseTextLine (TYPE_2__*) ; 

void HUlib_eraseSText(hu_stext_t* s)
{

    int i;

    for (i=0 ; i<s->h ; i++)
    {
	if (s->laston && !*s->on)
	    s->l[i].needsupdate = 4;
	HUlib_eraseTextLine(&s->l[i]);
    }
    s->laston = *s->on;

}