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
struct xv_pool {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct xv_pool*) ; 

void xv_destroy_pool(struct xv_pool *pool)
{
	kfree(pool);
}