#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned long entry; unsigned long tag; int children; struct TYPE_5__* next; int /*<<< orphan*/ * last_attr; int /*<<< orphan*/ * first_attr; } ;
typedef  TYPE_1__ abbrev_entry ;

/* Variables and functions */
 TYPE_1__* first_abbrev ; 
 TYPE_1__* last_abbrev ; 
 TYPE_1__* malloc (int) ; 

__attribute__((used)) static void
add_abbrev (unsigned long number, unsigned long tag, int children)
{
  abbrev_entry *entry;

  entry = malloc (sizeof (*entry));

  if (entry == NULL)
    /* ugg */
    return;

  entry->entry      = number;
  entry->tag        = tag;
  entry->children   = children;
  entry->first_attr = NULL;
  entry->last_attr  = NULL;
  entry->next       = NULL;

  if (first_abbrev == NULL)
    first_abbrev = entry;
  else
    last_abbrev->next = entry;

  last_abbrev = entry;
}