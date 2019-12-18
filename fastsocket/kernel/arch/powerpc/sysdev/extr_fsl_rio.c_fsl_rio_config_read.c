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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct rio_priv {scalar_t__ maint_win; TYPE_1__* maint_atmu_regs; } ;
struct rio_mport {struct rio_priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  rowtar; } ;

/* Variables and functions */
 int in_8 (int*) ; 
 int in_be16 (int*) ; 
 int in_be32 (int*) ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,int,int,int) ; 

__attribute__((used)) static int
fsl_rio_config_read(struct rio_mport *mport, int index, u16 destid,
			u8 hopcount, u32 offset, int len, u32 *val)
{
	struct rio_priv *priv = mport->priv;
	u8 *data;

	pr_debug
	    ("fsl_rio_config_read: index %d destid %d hopcount %d offset %8.8x len %d\n",
	     index, destid, hopcount, offset, len);
	out_be32(&priv->maint_atmu_regs->rowtar,
		 (destid << 22) | (hopcount << 12) | ((offset & ~0x3) >> 9));

	data = (u8 *) priv->maint_win + offset;
	switch (len) {
	case 1:
		*val = in_8((u8 *) data);
		break;
	case 2:
		*val = in_be16((u16 *) data);
		break;
	default:
		*val = in_be32((u32 *) data);
		break;
	}

	return 0;
}