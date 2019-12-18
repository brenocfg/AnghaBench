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
struct nv04_bus_priv {int /*<<< orphan*/  base; } ;
struct nouveau_object {int dummy; } ;

/* Variables and functions */
 int nouveau_bus_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv04_bus_priv*,int,int) ; 

__attribute__((used)) static int
nv04_bus_init(struct nouveau_object *object)
{
	struct nv04_bus_priv *priv = (void *)object;

	nv_wr32(priv, 0x001100, 0xffffffff);
	nv_wr32(priv, 0x001140, 0x00000111);

	return nouveau_bus_init(&priv->base);
}