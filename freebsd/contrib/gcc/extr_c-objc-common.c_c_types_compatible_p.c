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
 int /*<<< orphan*/  TYPE_MAIN_VARIANT (int /*<<< orphan*/ ) ; 
 int comptypes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
c_types_compatible_p (tree x, tree y)
{
    return comptypes (TYPE_MAIN_VARIANT (x), TYPE_MAIN_VARIANT (y));
}