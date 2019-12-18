#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nv50_i2c_priv {int dummy; } ;
struct nv50_i2c_port {int state; int /*<<< orphan*/  addr; } ;
struct nouveau_i2c_port {int dummy; } ;
struct TYPE_2__ {scalar_t__ engine; } ;

/* Variables and functions */
 TYPE_1__* nv_object (struct nouveau_i2c_port*) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv50_i2c_priv*,int /*<<< orphan*/ ,int) ; 

void
nv50_i2c_drive_sda(struct nouveau_i2c_port *base, int state)
{
	struct nv50_i2c_priv *priv = (void *)nv_object(base)->engine;
	struct nv50_i2c_port *port = (void *)base;
	if (state) port->state |= 0x02;
	else	   port->state &= 0xfd;
	nv_wr32(priv, port->addr, port->state);
}