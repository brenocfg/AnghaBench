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
struct i2c_pca_pf_data {scalar_t__ reg_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite8 (int,scalar_t__) ; 

__attribute__((used)) static void i2c_pca_pf_writebyte16(void *pd, int reg, int val)
{
	struct i2c_pca_pf_data *i2c = pd;
	iowrite8(val, i2c->reg_base + reg * 2);
}