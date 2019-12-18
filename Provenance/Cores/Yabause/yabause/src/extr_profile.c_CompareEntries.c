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
struct TYPE_2__ {int l_total_ms; } ;
typedef  TYPE_1__ entry_t ;

/* Variables and functions */

__attribute__((used)) static int CompareEntries (const void* p_1, const void* p_2) {
  entry_t* p_entry1, *p_entry2 ;
  /* Cast elements to entry_t type */
  p_entry1 = (entry_t*) p_1 ;
  p_entry2 = (entry_t*) p_2 ;
  /* Compare */
  return p_entry2->l_total_ms - p_entry1->l_total_ms ; 
}