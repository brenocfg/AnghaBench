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
struct page_entry {int dummy; } ;

/* Variables and functions */
 struct page_entry* lookup_page_table_entry (void const*) ; 

__attribute__((used)) static inline struct page_entry *
zone_get_object_page (const void *object)
{
  return lookup_page_table_entry (object);
}