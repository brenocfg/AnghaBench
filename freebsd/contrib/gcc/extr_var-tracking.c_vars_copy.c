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
typedef  int /*<<< orphan*/  htab_t ;

/* Variables and functions */
 int /*<<< orphan*/  htab_traverse (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vars_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vars_copy_1 ; 

__attribute__((used)) static void
vars_copy (htab_t dst, htab_t src)
{
  vars_clear (dst);
  htab_traverse (src, vars_copy_1, dst);
}