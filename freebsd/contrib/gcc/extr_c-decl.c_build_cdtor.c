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
typedef  scalar_t__ tree ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_INIT_PRIORITY ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  append_to_statement_list (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  build_function_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgraph_build_static_cdtor (int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
build_cdtor (int method_type, tree cdtors)
{
  tree body = 0;

  if (!cdtors)
    return;

  for (; cdtors; cdtors = TREE_CHAIN (cdtors))
    append_to_statement_list (build_function_call (TREE_VALUE (cdtors), 0),
			      &body);

  cgraph_build_static_cdtor (method_type, body, DEFAULT_INIT_PRIORITY);
}