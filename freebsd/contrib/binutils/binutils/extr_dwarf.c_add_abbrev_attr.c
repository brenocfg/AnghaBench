#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned long attribute; unsigned long form; struct TYPE_4__* next; } ;
typedef  TYPE_1__ abbrev_attr ;
struct TYPE_5__ {TYPE_1__* last_attr; TYPE_1__* first_attr; } ;

/* Variables and functions */
 TYPE_3__* last_abbrev ; 
 TYPE_1__* malloc (int) ; 

__attribute__((used)) static void
add_abbrev_attr (unsigned long attribute, unsigned long form)
{
  abbrev_attr *attr;

  attr = malloc (sizeof (*attr));

  if (attr == NULL)
    /* ugg */
    return;

  attr->attribute = attribute;
  attr->form      = form;
  attr->next      = NULL;

  if (last_abbrev->first_attr == NULL)
    last_abbrev->first_attr = attr;
  else
    last_abbrev->last_attr->next = attr;

  last_abbrev->last_attr = attr;
}