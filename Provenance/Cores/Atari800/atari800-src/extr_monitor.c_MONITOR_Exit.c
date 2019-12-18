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
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * trainer_flags ; 
 int /*<<< orphan*/ * trainer_memory ; 

void MONITOR_Exit(void)
{
	if (trainer_memory != NULL) {
		free(trainer_memory);
		trainer_memory=NULL;
		trainer_flags=NULL;
	}
}