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
 scalar_t__ declare_global_var (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dso_handle_node ; 
 int /*<<< orphan*/  get_identifier (char*) ; 
 int /*<<< orphan*/  ptr_type_node ; 

__attribute__((used)) static tree
get_dso_handle_node (void)
{
  if (dso_handle_node)
    return dso_handle_node;

  /* Declare the variable.  */
  dso_handle_node = declare_global_var (get_identifier ("__dso_handle"),
					ptr_type_node);

  return dso_handle_node;
}