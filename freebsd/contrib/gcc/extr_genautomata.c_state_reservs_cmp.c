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
typedef  int /*<<< orphan*/  reserv_sets_t ;

/* Variables and functions */
 int reserv_sets_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
state_reservs_cmp (const void *reservs_ptr_1, const void *reservs_ptr_2)
{
  return reserv_sets_cmp (*(reserv_sets_t *) reservs_ptr_1,
                          *(reserv_sets_t *) reservs_ptr_2);
}