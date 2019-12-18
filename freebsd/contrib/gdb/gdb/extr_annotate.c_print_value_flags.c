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
struct type {int dummy; } ;

/* Variables and functions */
 scalar_t__ can_dereference (struct type*) ; 
 int /*<<< orphan*/  printf_filtered (char*) ; 

__attribute__((used)) static void
print_value_flags (struct type *t)
{
  if (can_dereference (t))
    printf_filtered ("*");
  else
    printf_filtered ("-");
}