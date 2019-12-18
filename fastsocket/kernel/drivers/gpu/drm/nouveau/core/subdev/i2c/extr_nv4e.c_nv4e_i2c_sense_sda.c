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
struct nv4e_i2c_priv {int dummy; } ;
struct nv4e_i2c_port {int /*<<< orphan*/  addr; } ;
struct nouveau_i2c_port {int dummy; } ;
struct TYPE_2__ {scalar_t__ engine; } ;

/* Variables and functions */
 TYPE_1__* nv_object (struct nouveau_i2c_port*) ; 
 int nv_rd32 (struct nv4e_i2c_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nv4e_i2c_sense_sda(struct nouveau_i2c_port *base)
{
	struct nv4e_i2c_priv *priv = (void *)nv_object(base)->engine;
	struct nv4e_i2c_port *port = (void *)base;
	return !!(nv_rd32(priv, port->addr) & 0x00080000);
}