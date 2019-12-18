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
 int arenasize ; 
 int /*<<< orphan*/  initialize_arena_element (int) ; 

void initialize_arena(void) {
	for (int i = 0; i < arenasize; i++) {
		initialize_arena_element(i);
	}
}