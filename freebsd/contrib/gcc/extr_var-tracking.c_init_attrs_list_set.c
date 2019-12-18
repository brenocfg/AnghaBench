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
typedef  int /*<<< orphan*/ * attrs ;

/* Variables and functions */
 int FIRST_PSEUDO_REGISTER ; 

__attribute__((used)) static void
init_attrs_list_set (attrs *set)
{
  int i;

  for (i = 0; i < FIRST_PSEUDO_REGISTER; i++)
    set[i] = NULL;
}