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
struct c_declspecs {int declspecs_seen_p; int /*<<< orphan*/  attrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  chainon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct c_declspecs *
declspecs_add_attrs (struct c_declspecs *specs, tree attrs)
{
  specs->attrs = chainon (attrs, specs->attrs);
  specs->declspecs_seen_p = true;
  return specs;
}