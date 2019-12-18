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
struct TYPE_3__ {int /*<<< orphan*/  order; } ;
typedef  TYPE_1__ page_entry ;

/* Variables and functions */
 size_t OBJECT_SIZE (int /*<<< orphan*/ ) ; 
 TYPE_1__* lookup_page_table_entry (void const*) ; 

size_t
ggc_get_size (const void *p)
{
  page_entry *pe = lookup_page_table_entry (p);
  return OBJECT_SIZE (pe->order);
}