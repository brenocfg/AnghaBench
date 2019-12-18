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
struct ptr_loc {int dummy; } ;

/* Variables and functions */
 scalar_t__ htab_find (int /*<<< orphan*/ ,void const**) ; 
 int /*<<< orphan*/  ptr_locs ; 

__attribute__((used)) static const struct ptr_loc *
get_rtx_ptr_loc (const void *ptr)
{
  return (const struct ptr_loc *) htab_find (ptr_locs, &ptr);
}