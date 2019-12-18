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
struct nv84_crypt_priv {int /*<<< orphan*/  base; } ;
struct nouveau_object {int dummy; } ;

/* Variables and functions */
 int nouveau_engine_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv84_crypt_priv*,int,int) ; 

__attribute__((used)) static int
nv84_crypt_init(struct nouveau_object *object)
{
	struct nv84_crypt_priv *priv = (void *)object;
	int ret;

	ret = nouveau_engine_init(&priv->base);
	if (ret)
		return ret;

	nv_wr32(priv, 0x102130, 0xffffffff);
	nv_wr32(priv, 0x102140, 0xffffffbf);
	nv_wr32(priv, 0x10200c, 0x00000010);
	return 0;
}