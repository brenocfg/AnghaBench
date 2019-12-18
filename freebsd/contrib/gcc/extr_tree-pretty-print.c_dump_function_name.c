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
typedef  int /*<<< orphan*/  pretty_printer ;

/* Variables and functions */
 scalar_t__ DECL_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINT_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_decl_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dump_function_name (pretty_printer *buffer, tree node)
{
  if (DECL_NAME (node))
    PRINT_FUNCTION_NAME (node);
  else
    dump_decl_name (buffer, node, 0);
}