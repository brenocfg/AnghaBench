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
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  implicit_any_map ; 
 int /*<<< orphan*/  map_put (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 

void set_implicit_any(Expr *expr) {
    map_put(&implicit_any_map, expr, (void *)1);
}