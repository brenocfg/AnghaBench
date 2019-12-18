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
typedef  int /*<<< orphan*/  u32 ;
struct nv04_i2c_priv {int dummy; } ;
struct nouveau_oclass {int dummy; } ;
struct nouveau_object {int dummy; } ;

/* Variables and functions */
 int nouveau_i2c_create (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,int /*<<< orphan*/ ,struct nv04_i2c_priv**) ; 
 int /*<<< orphan*/  nv04_i2c_sclass ; 
 struct nouveau_object* nv_object (struct nv04_i2c_priv*) ; 

__attribute__((used)) static int
nv04_i2c_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
	      struct nouveau_oclass *oclass, void *data, u32 size,
	      struct nouveau_object **pobject)
{
	struct nv04_i2c_priv *priv;
	int ret;

	ret = nouveau_i2c_create(parent, engine, oclass, nv04_i2c_sclass, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	return 0;
}