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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int /*<<< orphan*/  expand_or_defer_fn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_compound_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_function (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
finish_static_storage_duration_function (tree body)
{
  /* Close out the function.  */
  finish_compound_stmt (body);
  expand_or_defer_fn (finish_function (0));
}