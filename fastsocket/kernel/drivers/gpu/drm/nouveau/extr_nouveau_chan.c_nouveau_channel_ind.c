#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct nve0_channel_ind_class {int ilength; int /*<<< orphan*/  engine; scalar_t__ ioffset; int /*<<< orphan*/  pushbuf; } ;
struct nouveau_drm {int dummy; } ;
struct nouveau_cli {int dummy; } ;
struct TYPE_3__ {scalar_t__ offset; } ;
struct TYPE_4__ {TYPE_1__ vma; int /*<<< orphan*/  handle; } ;
struct nouveau_channel {int /*<<< orphan*/  object; TYPE_2__ push; } ;
typedef  int /*<<< orphan*/  args ;

/* Variables and functions */
#define  NV50_CHANNEL_IND_CLASS 131 
#define  NV84_CHANNEL_IND_CLASS 130 
#define  NVC0_CHANNEL_IND_CLASS 129 
#define  NVE0_CHANNEL_IND_CLASS 128 
 int /*<<< orphan*/  nouveau_channel_del (struct nouveau_channel**) ; 
 int nouveau_channel_prep (struct nouveau_drm*,struct nouveau_cli*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct nouveau_channel**) ; 
 int nouveau_object_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nve0_channel_ind_class*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nv_object (struct nouveau_cli*) ; 

__attribute__((used)) static int
nouveau_channel_ind(struct nouveau_drm *drm, struct nouveau_cli *cli,
		    u32 parent, u32 handle, u32 engine,
		    struct nouveau_channel **pchan)
{
	static const u16 oclasses[] = { NVE0_CHANNEL_IND_CLASS,
					NVC0_CHANNEL_IND_CLASS,
					NV84_CHANNEL_IND_CLASS,
					NV50_CHANNEL_IND_CLASS,
					0 };
	const u16 *oclass = oclasses;
	struct nve0_channel_ind_class args;
	struct nouveau_channel *chan;
	int ret;

	/* allocate dma push buffer */
	ret = nouveau_channel_prep(drm, cli, parent, handle, 0x12000, &chan);
	*pchan = chan;
	if (ret)
		return ret;

	/* create channel object */
	args.pushbuf = chan->push.handle;
	args.ioffset = 0x10000 + chan->push.vma.offset;
	args.ilength = 0x02000;
	args.engine  = engine;

	do {
		ret = nouveau_object_new(nv_object(cli), parent, handle,
					 *oclass++, &args, sizeof(args),
					 &chan->object);
		if (ret == 0)
			return ret;
	} while (*oclass);

	nouveau_channel_del(pchan);
	return ret;
}