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
struct nv50_i2c_port {int data; scalar_t__ ctrl; } ;
struct nouveau_i2c_port {int dummy; } ;
struct TYPE_2__ {scalar_t__ engine; } ;

/* Variables and functions */
 int /*<<< orphan*/  nv_mask (struct nv50_i2c_priv*,scalar_t__,int,int) ; 
 TYPE_1__* nv_object (struct nouveau_i2c_port*) ; 

void
nv94_i2c_acquire(struct nouveau_i2c_port *base)
{
	struct nv50_i2c_priv *priv = (void *)nv_object(base)->engine;
	struct nv50_i2c_port *port = (void *)base;
	if (port->ctrl) {
		nv_mask(priv, port->ctrl + 0x0c, 0x00000001, 0x00000000);
		nv_mask(priv, port->ctrl + 0x00, 0x0000f003, port->data);
	}
}