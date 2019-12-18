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
typedef  int /*<<< orphan*/  bt_bdaddr_t ;

/* Variables and functions */
 int bdaddr_equals (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool bdaddr_equality_fn(const void *x, const void *y)
{
    return bdaddr_equals((bt_bdaddr_t *)x, (bt_bdaddr_t *)y);
}