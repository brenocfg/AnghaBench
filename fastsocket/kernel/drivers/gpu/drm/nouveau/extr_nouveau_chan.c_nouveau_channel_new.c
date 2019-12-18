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
struct nouveau_drm {int dummy; } ;
struct nouveau_cli {int dummy; } ;
struct nouveau_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV_DEBUG (struct nouveau_cli*,char*,int) ; 
 int /*<<< orphan*/  NV_ERROR (struct nouveau_cli*,char*,int) ; 
 int /*<<< orphan*/  nouveau_channel_del (struct nouveau_channel**) ; 
 int nouveau_channel_dma (struct nouveau_drm*,struct nouveau_cli*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nouveau_channel**) ; 
 int nouveau_channel_ind (struct nouveau_drm*,struct nouveau_cli*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nouveau_channel**) ; 
 int nouveau_channel_init (struct nouveau_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
nouveau_channel_new(struct nouveau_drm *drm, struct nouveau_cli *cli,
		    u32 parent, u32 handle, u32 arg0, u32 arg1,
		    struct nouveau_channel **pchan)
{
	int ret;

	ret = nouveau_channel_ind(drm, cli, parent, handle, arg0, pchan);
	if (ret) {
		NV_DEBUG(cli, "ib channel create, %d\n", ret);
		ret = nouveau_channel_dma(drm, cli, parent, handle, pchan);
		if (ret) {
			NV_DEBUG(cli, "dma channel create, %d\n", ret);
			return ret;
		}
	}

	ret = nouveau_channel_init(*pchan, arg0, arg1);
	if (ret) {
		NV_ERROR(cli, "channel failed to initialise, %d\n", ret);
		nouveau_channel_del(pchan);
		return ret;
	}

	return 0;
}