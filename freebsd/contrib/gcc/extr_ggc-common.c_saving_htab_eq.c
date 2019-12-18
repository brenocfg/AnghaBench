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
struct ptr_data {void const* obj; } ;

/* Variables and functions */

__attribute__((used)) static int
saving_htab_eq (const void *p1, const void *p2)
{
  return ((struct ptr_data *)p1)->obj == p2;
}