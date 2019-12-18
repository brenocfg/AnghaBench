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
typedef  int /*<<< orphan*/  Type ;

/* Variables and functions */
 int /*<<< orphan*/  get_reachable (int /*<<< orphan*/ *) ; 
 int is_reachable (int /*<<< orphan*/ ) ; 

bool is_tuple_reachable(Type *type) {
    return is_reachable(get_reachable(type));
}