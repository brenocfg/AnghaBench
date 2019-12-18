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
struct i2o_controller {int /*<<< orphan*/  in_msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2o_pool_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct i2o_controller*) ; 

__attribute__((used)) static inline void i2o_iop_free(struct i2o_controller *c)
{
	i2o_pool_free(&c->in_msg);
	kfree(c);
}