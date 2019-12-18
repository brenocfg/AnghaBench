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
 int /*<<< orphan*/  global_spawn_accept ; 
 int percpu_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int fsocket_need_global_accept(void)
{
	return percpu_read(global_spawn_accept) & 0x1;
}