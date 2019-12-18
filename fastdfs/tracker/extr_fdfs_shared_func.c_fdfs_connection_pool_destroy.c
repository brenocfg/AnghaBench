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

/* Variables and functions */
 int /*<<< orphan*/  conn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_connection_pool ; 

void fdfs_connection_pool_destroy()
{
	conn_pool_destroy(&g_connection_pool);
}