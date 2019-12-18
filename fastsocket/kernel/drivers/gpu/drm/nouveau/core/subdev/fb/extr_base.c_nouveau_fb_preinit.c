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
struct TYPE_2__ {int (* init ) (struct nouveau_fb*) ;int size; size_t type; } ;
struct nouveau_fb {TYPE_1__ ram; int /*<<< orphan*/  tags; int /*<<< orphan*/  vram; } ;

/* Variables and functions */
 int ERANGE ; 
#define  NV_MEM_TYPE_DDR1 138 
#define  NV_MEM_TYPE_DDR2 137 
#define  NV_MEM_TYPE_DDR3 136 
#define  NV_MEM_TYPE_GDDR2 135 
#define  NV_MEM_TYPE_GDDR3 134 
#define  NV_MEM_TYPE_GDDR4 133 
#define  NV_MEM_TYPE_GDDR5 132 
#define  NV_MEM_TYPE_SDRAM 131 
#define  NV_MEM_TYPE_SGRAM 130 
#define  NV_MEM_TYPE_STOLEN 129 
#define  NV_MEM_TYPE_UNKNOWN 128 
 int nouveau_mm_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  nouveau_mm_initialised (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nv_fatal (struct nouveau_fb*,char*) ; 
 int /*<<< orphan*/  nv_info (struct nouveau_fb*,char*,...) ; 
 int stub1 (struct nouveau_fb*) ; 

int
nouveau_fb_preinit(struct nouveau_fb *pfb)
{
	static const char *name[] = {
		[NV_MEM_TYPE_UNKNOWN] = "unknown",
		[NV_MEM_TYPE_STOLEN ] = "stolen system memory",
		[NV_MEM_TYPE_SGRAM  ] = "SGRAM",
		[NV_MEM_TYPE_SDRAM  ] = "SDRAM",
		[NV_MEM_TYPE_DDR1   ] = "DDR1",
		[NV_MEM_TYPE_DDR2   ] = "DDR2",
		[NV_MEM_TYPE_DDR3   ] = "DDR3",
		[NV_MEM_TYPE_GDDR2  ] = "GDDR2",
		[NV_MEM_TYPE_GDDR3  ] = "GDDR3",
		[NV_MEM_TYPE_GDDR4  ] = "GDDR4",
		[NV_MEM_TYPE_GDDR5  ] = "GDDR5",
	};
	int ret, tags;

	tags = pfb->ram.init(pfb);
	if (tags < 0 || !pfb->ram.size) {
		nv_fatal(pfb, "error detecting memory configuration!!\n");
		return (tags < 0) ? tags : -ERANGE;
	}

	if (!nouveau_mm_initialised(&pfb->vram)) {
		ret = nouveau_mm_init(&pfb->vram, 0, pfb->ram.size >> 12, 1);
		if (ret)
			return ret;
	}

	if (!nouveau_mm_initialised(&pfb->tags)) {
		ret = nouveau_mm_init(&pfb->tags, 0, tags ? ++tags : 0, 1);
		if (ret)
			return ret;
	}

	nv_info(pfb, "RAM type: %s\n", name[pfb->ram.type]);
	nv_info(pfb, "RAM size: %d MiB\n", (int)(pfb->ram.size >> 20));
	nv_info(pfb, "   ZCOMP: %d tags\n", tags);
	return 0;
}