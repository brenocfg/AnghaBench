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
 int /*<<< orphan*/  ADDR_EXPR ; 
 int /*<<< orphan*/  build_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_unary_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ processing_template_decl ; 

__attribute__((used)) static tree
build_this (tree obj)
{
  /* In a template, we are only concerned about the type of the
     expression, so we can take a shortcut.  */
  if (processing_template_decl)
    return build_address (obj);

  return build_unary_op (ADDR_EXPR, obj, 0);
}