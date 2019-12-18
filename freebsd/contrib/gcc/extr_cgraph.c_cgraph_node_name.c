#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cgraph_node {int /*<<< orphan*/  decl; } ;
struct TYPE_2__ {char const* (* decl_printable_name ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 TYPE_1__ lang_hooks ; 
 char const* stub1 (int /*<<< orphan*/ ,int) ; 

const char *
cgraph_node_name (struct cgraph_node *node)
{
  return lang_hooks.decl_printable_name (node->decl, 2);
}