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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  smem_page_start; int /*<<< orphan*/  host_page_num_fn; int /*<<< orphan*/  smem_pg0; } ;
struct bfa_ioc_s {TYPE_1__ ioc_regs; int /*<<< orphan*/  port1_mode; int /*<<< orphan*/  port0_mode; int /*<<< orphan*/  asic_mode; int /*<<< orphan*/  asic_gen; } ;

/* Variables and functions */
 scalar_t__ BFA_IOC_FLASH_CHUNK_ADDR (scalar_t__) ; 
 scalar_t__ BFA_IOC_FLASH_CHUNK_NO (scalar_t__) ; 
 size_t BFA_IOC_FLASH_OFFSET_IN_CHUNK (scalar_t__) ; 
 scalar_t__ BFI_FWBOOT_DEVMODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ BFI_FWBOOT_DEVMODE_OFF ; 
 scalar_t__ BFI_FWBOOT_ENV_OFF ; 
 scalar_t__ BFI_FWBOOT_TYPE_OFF ; 
 scalar_t__ PSS_SMEM_PGNUM (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ PSS_SMEM_PGOFF (scalar_t__) ; 
 scalar_t__* bfa_cb_image_get_chunk (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ bfa_cb_image_get_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_asic_gen (struct bfa_ioc_s*) ; 
 int /*<<< orphan*/  bfa_mem_write (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_ioc_s*,scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  swab32 (scalar_t__) ; 
 int /*<<< orphan*/  writel (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_ioc_download_fw(struct bfa_ioc_s *ioc, u32 boot_type,
		    u32 boot_env)
{
	u32 *fwimg;
	u32 pgnum, pgoff;
	u32 loff = 0;
	u32 chunkno = 0;
	u32 i;
	u32 asicmode;

	bfa_trc(ioc, bfa_cb_image_get_size(bfa_ioc_asic_gen(ioc)));
	fwimg = bfa_cb_image_get_chunk(bfa_ioc_asic_gen(ioc), chunkno);

	pgnum = PSS_SMEM_PGNUM(ioc->ioc_regs.smem_pg0, loff);
	pgoff = PSS_SMEM_PGOFF(loff);

	writel(pgnum, ioc->ioc_regs.host_page_num_fn);

	for (i = 0; i < bfa_cb_image_get_size(bfa_ioc_asic_gen(ioc)); i++) {

		if (BFA_IOC_FLASH_CHUNK_NO(i) != chunkno) {
			chunkno = BFA_IOC_FLASH_CHUNK_NO(i);
			fwimg = bfa_cb_image_get_chunk(bfa_ioc_asic_gen(ioc),
					BFA_IOC_FLASH_CHUNK_ADDR(chunkno));
		}

		/*
		 * write smem
		 */
		bfa_mem_write(ioc->ioc_regs.smem_page_start, loff,
			cpu_to_le32(fwimg[BFA_IOC_FLASH_OFFSET_IN_CHUNK(i)]));

		loff += sizeof(u32);

		/*
		 * handle page offset wrap around
		 */
		loff = PSS_SMEM_PGOFF(loff);
		if (loff == 0) {
			pgnum++;
			writel(pgnum, ioc->ioc_regs.host_page_num_fn);
		}
	}

	writel(PSS_SMEM_PGNUM(ioc->ioc_regs.smem_pg0, 0),
			ioc->ioc_regs.host_page_num_fn);

	/*
	 * Set boot type and device mode at the end.
	 */
	asicmode = BFI_FWBOOT_DEVMODE(ioc->asic_gen, ioc->asic_mode,
				ioc->port0_mode, ioc->port1_mode);
	bfa_mem_write(ioc->ioc_regs.smem_page_start, BFI_FWBOOT_DEVMODE_OFF,
			swab32(asicmode));
	bfa_mem_write(ioc->ioc_regs.smem_page_start, BFI_FWBOOT_TYPE_OFF,
			swab32(boot_type));
	bfa_mem_write(ioc->ioc_regs.smem_page_start, BFI_FWBOOT_ENV_OFF,
			swab32(boot_env));
}