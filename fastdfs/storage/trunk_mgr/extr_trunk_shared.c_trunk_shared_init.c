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
 int /*<<< orphan*/  base64_init_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char,char,char) ; 
 int /*<<< orphan*/  g_fdfs_base64_context ; 

void trunk_shared_init()
{
	base64_init_ex(&g_fdfs_base64_context, 0, '-', '_', '.');
}