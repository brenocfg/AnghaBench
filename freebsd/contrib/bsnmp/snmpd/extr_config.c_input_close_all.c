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
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_close () ; 
 int /*<<< orphan*/  inputs ; 

__attribute__((used)) static void
input_close_all(void)
{
	while (!LIST_EMPTY(&inputs))
		input_close();
}