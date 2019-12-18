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
typedef  scalar_t__ u32 ;
struct nv04_instmem_priv {int /*<<< orphan*/  created; } ;
struct nouveau_object {int /*<<< orphan*/  refcount; } ;
struct nouveau_instmem {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int nouveau_object_ctor (struct nouveau_object*,struct nouveau_object*,int /*<<< orphan*/ *,void*,scalar_t__,struct nouveau_object**) ; 
 int /*<<< orphan*/  nv04_instobj_oclass ; 
 struct nouveau_object* nv_object (struct nouveau_instmem*) ; 
 scalar_t__ unlikely (int) ; 

int
nv04_instmem_alloc(struct nouveau_instmem *imem, struct nouveau_object *parent,
		   u32 size, u32 align, struct nouveau_object **pobject)
{
	struct nouveau_object *engine = nv_object(imem);
	struct nv04_instmem_priv *priv = (void *)(imem);
	int ret;

	ret = nouveau_object_ctor(parent, engine, &nv04_instobj_oclass,
				  (void *)(unsigned long)align, size, pobject);
	if (ret)
		return ret;

	/* INSTMEM itself creates objects to reserve (and preserve across
	 * suspend/resume) various fixed data locations, each one of these
	 * takes a reference on INSTMEM itself, causing it to never be
	 * freed.  We drop all the self-references here to avoid this.
	 */
	if (unlikely(!priv->created))
		atomic_dec(&engine->refcount);

	return 0;
}