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
struct nv50_disp_chan {int chid; } ;
struct nv50_disp_base {int chan; } ;
struct nouveau_oclass {int dummy; } ;
struct nouveau_object {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 unsigned long long NVDEV_ENGINE_DMAOBJ ; 
 int nouveau_namedb_create_ (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long long,int,void**) ; 

int
nv50_disp_chan_create_(struct nouveau_object *parent,
		       struct nouveau_object *engine,
		       struct nouveau_oclass *oclass, int chid,
		       int length, void **pobject)
{
	struct nv50_disp_base *base = (void *)parent;
	struct nv50_disp_chan *chan;
	int ret;

	if (base->chan & (1 << chid))
		return -EBUSY;
	base->chan |= (1 << chid);

	ret = nouveau_namedb_create_(parent, engine, oclass, 0, NULL,
				     (1ULL << NVDEV_ENGINE_DMAOBJ),
				     length, pobject);
	chan = *pobject;
	if (ret)
		return ret;

	chan->chid = chid;
	return 0;
}