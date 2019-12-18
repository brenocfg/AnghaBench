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
typedef  int /*<<< orphan*/  tree ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
struct TYPE_2__ {int /*<<< orphan*/  spec; } ;

/* Variables and functions */
 TYPE_1__ parser_xref_tag (int,int /*<<< orphan*/ ) ; 

tree
xref_tag (enum tree_code code, tree name)
{
  return parser_xref_tag (code, name).spec;
}