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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct nv50_chan {int /*<<< orphan*/  handle; int /*<<< orphan*/  user; } ;
struct nouveau_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVO_CHAN_HANDLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVO_CHAN_OCLASS (int /*<<< orphan*/ ,struct nouveau_object*) ; 
 int /*<<< orphan*/  EVO_CORE_HANDLE ; 
 int /*<<< orphan*/  NV_CLIENT_CLASS ; 
 int nouveau_object_new (struct nouveau_object*,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct nouveau_object* nv_pclass (struct nouveau_object*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nv50_chan_create(struct nouveau_object *core, u32 bclass, u8 head,
		 void *data, u32 size, struct nv50_chan *chan)
{
	struct nouveau_object *client = nv_pclass(core, NV_CLIENT_CLASS);
	const u32 oclass = EVO_CHAN_OCLASS(bclass, core);
	const u32 handle = EVO_CHAN_HANDLE(bclass, head);
	int ret;

	ret = nouveau_object_new(client, EVO_CORE_HANDLE, handle,
				 oclass, data, size, &chan->user);
	if (ret)
		return ret;

	chan->handle = handle;
	return 0;
}