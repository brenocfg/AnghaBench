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
 int TYPE_QUALS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_build_qualified_type (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static tree
qualify_type (tree type, tree like)
{
  return c_build_qualified_type (type,
				 TYPE_QUALS (type) | TYPE_QUALS (like));
}