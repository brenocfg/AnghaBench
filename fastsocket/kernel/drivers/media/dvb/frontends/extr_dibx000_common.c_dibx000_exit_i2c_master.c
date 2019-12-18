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
struct dibx000_i2c_master {int /*<<< orphan*/  gated_tuner_i2c_adap; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 

void dibx000_exit_i2c_master(struct dibx000_i2c_master *mst)
{
	i2c_del_adapter(&mst->gated_tuner_i2c_adap);
}