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
 int /*<<< orphan*/  DECL_CONTEXT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_CONTEXT (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_P (int /*<<< orphan*/ ) ; 

tree
get_containing_scope (tree t)
{
  return (TYPE_P (t) ? TYPE_CONTEXT (t) : DECL_CONTEXT (t));
}