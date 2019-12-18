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
 int /*<<< orphan*/  generate_states () ; 
 int /*<<< orphan*/  set_derives () ; 
 int /*<<< orphan*/  set_nullable () ; 

void
lr0(void)
{
    set_derives();
    set_nullable();
    generate_states();
}