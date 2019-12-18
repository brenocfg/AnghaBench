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
struct nv50_i2c_priv {int dummy; } ;
struct nv50_i2c_port {int /*<<< orphan*/  base; int /*<<< orphan*/  state; int /*<<< orphan*/  addr; } ;
struct nouveau_object {scalar_t__ engine; } ;

/* Variables and functions */
 int nouveau_i2c_port_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv50_i2c_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
nv50_i2c_port_init(struct nouveau_object *object)
{
	struct nv50_i2c_priv *priv = (void *)object->engine;
	struct nv50_i2c_port *port = (void *)object;
	nv_wr32(priv, port->addr, port->state);
	return nouveau_i2c_port_init(&port->base);
}