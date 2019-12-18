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
struct mtd_info {int dummy; } ;
struct map_info {struct cfi_private* fldrv_priv; } ;
struct cfi_private {TYPE_1__* cfiq; } ;
typedef  int __u16 ;
struct TYPE_2__ {int P_ID; int A_ID; } ;

/* Variables and functions */
 int P_ID_NONE ; 
 int P_ID_RESERVED ; 
 struct mtd_info* cfi_cmdset_0001 (struct map_info*,int) ; 
 struct mtd_info* cfi_cmdset_0002 (struct map_info*,int) ; 
 struct mtd_info* cfi_cmdset_0020 (struct map_info*,int) ; 
 struct mtd_info* cfi_cmdset_unknown (struct map_info*,int) ; 

__attribute__((used)) static struct mtd_info *check_cmd_set(struct map_info *map, int primary)
{
	struct cfi_private *cfi = map->fldrv_priv;
	__u16 type = primary?cfi->cfiq->P_ID:cfi->cfiq->A_ID;

	if (type == P_ID_NONE || type == P_ID_RESERVED)
		return NULL;

	switch(type){
		/* We need these for the !CONFIG_MODULES case,
		   because symbol_get() doesn't work there */
#ifdef CONFIG_MTD_CFI_INTELEXT
	case 0x0001:
	case 0x0003:
	case 0x0200:
		return cfi_cmdset_0001(map, primary);
#endif
#ifdef CONFIG_MTD_CFI_AMDSTD
	case 0x0002:
		return cfi_cmdset_0002(map, primary);
#endif
#ifdef CONFIG_MTD_CFI_STAA
        case 0x0020:
		return cfi_cmdset_0020(map, primary);
#endif
	default:
		return cfi_cmdset_unknown(map, primary);
	}
}