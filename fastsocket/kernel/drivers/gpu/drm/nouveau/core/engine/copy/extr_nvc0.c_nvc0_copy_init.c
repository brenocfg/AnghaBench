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
struct nvc0_copy_priv {int /*<<< orphan*/  base; } ;
struct nouveau_object {int dummy; } ;

/* Variables and functions */
 scalar_t__ NVDEV_ENGINE_COPY0 ; 
 int nouveau_falcon_init (int /*<<< orphan*/ *) ; 
 scalar_t__ nv_engidx (struct nouveau_object*) ; 
 int /*<<< orphan*/  nv_wo32 (struct nvc0_copy_priv*,int,scalar_t__) ; 

__attribute__((used)) static int
nvc0_copy_init(struct nouveau_object *object)
{
	struct nvc0_copy_priv *priv = (void *)object;
	int ret;

	ret = nouveau_falcon_init(&priv->base);
	if (ret)
		return ret;

	nv_wo32(priv, 0x084, nv_engidx(object) - NVDEV_ENGINE_COPY0);
	return 0;
}