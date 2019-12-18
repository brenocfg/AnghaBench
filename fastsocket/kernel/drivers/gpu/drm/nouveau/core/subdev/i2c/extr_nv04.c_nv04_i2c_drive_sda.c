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
typedef  int u8 ;
struct nv04_i2c_priv {int dummy; } ;
struct nv04_i2c_port {int /*<<< orphan*/  drive; } ;
struct nouveau_i2c_port {int dummy; } ;
struct TYPE_2__ {scalar_t__ engine; } ;

/* Variables and functions */
 TYPE_1__* nv_object (struct nouveau_i2c_port*) ; 
 int nv_rdvgac (struct nv04_i2c_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_wrvgac (struct nv04_i2c_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
nv04_i2c_drive_sda(struct nouveau_i2c_port *base, int state)
{
	struct nv04_i2c_priv *priv = (void *)nv_object(base)->engine;
	struct nv04_i2c_port *port = (void *)base;
	u8 val = nv_rdvgac(priv, 0, port->drive);
	if (state) val |= 0x10;
	else	   val &= 0xef;
	nv_wrvgac(priv, 0, port->drive, val | 0x01);
}