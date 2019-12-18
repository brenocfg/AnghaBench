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
struct export_list {char const* name; int is_data; struct export_list* next; } ;

/* Variables and functions */
 struct export_list* export_head ; 
 scalar_t__ ggc_alloc (int) ; 

void
i386_pe_record_exported_symbol (const char *name, int is_data)
{
  struct export_list *p;

  p = (struct export_list *) ggc_alloc (sizeof *p);
  p->next = export_head;
  p->name = name;
  p->is_data = is_data;
  export_head = p;
}