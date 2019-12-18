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
struct ptr_data {scalar_t__ new_addr; } ;

/* Variables and functions */

__attribute__((used)) static int
compare_ptr_data (const void *p1_p, const void *p2_p)
{
  struct ptr_data *p1 = *(struct ptr_data *const *)p1_p;
  struct ptr_data *p2 = *(struct ptr_data *const *)p2_p;
  return (((size_t)p1->new_addr > (size_t)p2->new_addr)
	  - ((size_t)p1->new_addr < (size_t)p2->new_addr));
}