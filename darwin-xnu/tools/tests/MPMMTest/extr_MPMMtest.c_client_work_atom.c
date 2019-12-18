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
 int PAGE_SIZE ; 
 scalar_t__* client_memory ; 
 int client_pages ; 

__attribute__((used)) static void
client_work_atom(void)
{
	static int	i;

	if (++i > client_pages * PAGE_SIZE / sizeof(long))
		i = 0;
	client_memory[i] = 0;
}