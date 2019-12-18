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
struct nouveau_i2c_port {int dummy; } ;
struct nouveau_i2c {struct nouveau_i2c_port* (* find_type ) (struct nouveau_i2c*,int /*<<< orphan*/ ) ;} ;
struct nouveau_disp {int dummy; } ;
struct dcb_output {int /*<<< orphan*/  extdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV_I2C_TYPE_EXTAUX (int /*<<< orphan*/ ) ; 
 struct nouveau_i2c* nouveau_i2c (struct nouveau_disp*) ; 
 struct nouveau_i2c_port* stub1 (struct nouveau_i2c*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nouveau_i2c_port *
nv50_pior_dp_find(struct nouveau_disp *disp, struct dcb_output *outp)
{
	struct nouveau_i2c *i2c = nouveau_i2c(disp);
	return i2c->find_type(i2c, NV_I2C_TYPE_EXTAUX(outp->extdev));
}