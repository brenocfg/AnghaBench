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
 int /*<<< orphan*/  LOOKUP_COMPLAIN ; 
 int /*<<< orphan*/  lookup_arg_dependent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lookup_name_real (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tree
lookup_function_nonclass (tree name, tree args, bool block_p)
{
  return
    lookup_arg_dependent (name,
			  lookup_name_real (name, 0, 1, block_p, 0,
					    LOOKUP_COMPLAIN),
			  args);
}