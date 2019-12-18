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
struct TYPE_3__ {struct TYPE_3__* next; int /*<<< orphan*/  text; } ;
typedef  TYPE_1__ dlist_type ;

/* Variables and functions */
 TYPE_1__* d_list ; 
 scalar_t__ xmalloc (int) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

void
def_description (const char *desc)
{
  dlist_type *d = (dlist_type *) xmalloc (sizeof (dlist_type));
  d->text = xstrdup (desc);
  d->next = d_list;
  d_list = d;
}