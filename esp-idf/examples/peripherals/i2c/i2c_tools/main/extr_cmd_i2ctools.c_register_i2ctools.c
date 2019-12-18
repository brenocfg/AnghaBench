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
 int /*<<< orphan*/  register_i2cconfig () ; 
 int /*<<< orphan*/  register_i2cdectect () ; 
 int /*<<< orphan*/  register_i2cdump () ; 
 int /*<<< orphan*/  register_i2cget () ; 
 int /*<<< orphan*/  register_i2cset () ; 

void register_i2ctools(void)
{
    register_i2cconfig();
    register_i2cdectect();
    register_i2cget();
    register_i2cset();
    register_i2cdump();
}