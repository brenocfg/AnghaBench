#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* pfp_fw; TYPE_1__* me_fw; } ;
typedef  TYPE_3__ drm_radeon_private_t ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_7__ {scalar_t__ data; } ;
struct TYPE_6__ {scalar_t__ data; } ;

/* Variables and functions */
 int PFP_UCODE_SIZE ; 
 int PM4_UCODE_SIZE ; 
 int R600_BUF_SWAP_32BIT ; 
 int /*<<< orphan*/  R600_CP_ME_RAM_DATA ; 
 int /*<<< orphan*/  R600_CP_ME_RAM_RADDR ; 
 int /*<<< orphan*/  R600_CP_ME_RAM_WADDR ; 
 int /*<<< orphan*/  R600_CP_PFP_UCODE_ADDR ; 
 int /*<<< orphan*/  R600_CP_PFP_UCODE_DATA ; 
 int /*<<< orphan*/  R600_CP_RB_CNTL ; 
 int /*<<< orphan*/  R600_GRBM_SOFT_RESET ; 
 int R600_RB_BLKSZ (int) ; 
 int R600_RB_BUFSZ (int) ; 
 int R600_RB_NO_UPDATE ; 
 int R600_SOFT_RESET_CP ; 
 int /*<<< orphan*/  RADEON_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RADEON_WRITE (int /*<<< orphan*/ ,int) ; 
 int be32_to_cpup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  r600_do_cp_stop (TYPE_3__*) ; 

__attribute__((used)) static void r600_cp_load_microcode(drm_radeon_private_t *dev_priv)
{
	const __be32 *fw_data;
	int i;

	if (!dev_priv->me_fw || !dev_priv->pfp_fw)
		return;

	r600_do_cp_stop(dev_priv);

	RADEON_WRITE(R600_CP_RB_CNTL,
#ifdef __BIG_ENDIAN
		     R600_BUF_SWAP_32BIT |
#endif
		     R600_RB_NO_UPDATE |
		     R600_RB_BLKSZ(15) |
		     R600_RB_BUFSZ(3));

	RADEON_WRITE(R600_GRBM_SOFT_RESET, R600_SOFT_RESET_CP);
	RADEON_READ(R600_GRBM_SOFT_RESET);
	mdelay(15);
	RADEON_WRITE(R600_GRBM_SOFT_RESET, 0);

	fw_data = (const __be32 *)dev_priv->me_fw->data;
	RADEON_WRITE(R600_CP_ME_RAM_WADDR, 0);
	for (i = 0; i < PM4_UCODE_SIZE * 3; i++)
		RADEON_WRITE(R600_CP_ME_RAM_DATA,
			     be32_to_cpup(fw_data++));

	fw_data = (const __be32 *)dev_priv->pfp_fw->data;
	RADEON_WRITE(R600_CP_PFP_UCODE_ADDR, 0);
	for (i = 0; i < PFP_UCODE_SIZE; i++)
		RADEON_WRITE(R600_CP_PFP_UCODE_DATA,
			     be32_to_cpup(fw_data++));

	RADEON_WRITE(R600_CP_PFP_UCODE_ADDR, 0);
	RADEON_WRITE(R600_CP_ME_RAM_WADDR, 0);
	RADEON_WRITE(R600_CP_ME_RAM_RADDR, 0);

}