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
 int /*<<< orphan*/  register_free () ; 
 int /*<<< orphan*/  register_make () ; 
 int /*<<< orphan*/  register_restart () ; 

void register_system(void)
{
    register_free();
    register_restart();
    register_make();
}