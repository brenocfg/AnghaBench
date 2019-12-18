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
typedef  int uint32_t ;
struct lpfc_hba {int dummy; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_BG ; 
 int /*<<< orphan*/  LOG_INIT ; 
 int PAGE_SHIFT ; 
 int SHOST_DIF_TYPE1_PROTECTION ; 
 int SHOST_DIX_GUARD_CRC ; 
 int SHOST_DIX_GUARD_IP ; 
 int SHOST_DIX_TYPE0_PROTECTION ; 
 int SHOST_DIX_TYPE1_PROTECTION ; 
 scalar_t__ __get_free_pages (int /*<<< orphan*/ ,int) ; 
 char* _dump_buf_data ; 
 int _dump_buf_data_order ; 
 char* _dump_buf_dif ; 
 int _dump_buf_dif_order ; 
 int /*<<< orphan*/  _dump_buf_lock ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int lpfc_prot_guard ; 
 int lpfc_prot_mask ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scsi_host_set_guard (struct Scsi_Host*,int) ; 
 int /*<<< orphan*/  scsi_host_set_prot (struct Scsi_Host*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
lpfc_setup_bg(struct lpfc_hba *phba, struct Scsi_Host *shost)
{
	uint32_t old_mask;
	uint32_t old_guard;

	int pagecnt = 10;
	if (lpfc_prot_mask && lpfc_prot_guard) {
		lpfc_printf_log(phba, KERN_INFO, LOG_INIT,
				"1478 Registering BlockGuard with the "
				"SCSI layer\n");

		old_mask = lpfc_prot_mask;
		old_guard = lpfc_prot_guard;

		/* Only allow supported values */
		lpfc_prot_mask &= (SHOST_DIF_TYPE1_PROTECTION |
			SHOST_DIX_TYPE0_PROTECTION |
			SHOST_DIX_TYPE1_PROTECTION);
		lpfc_prot_guard &= (SHOST_DIX_GUARD_IP | SHOST_DIX_GUARD_CRC);

		/* DIF Type 1 protection for profiles AST1/C1 is end to end */
		if (lpfc_prot_mask == SHOST_DIX_TYPE1_PROTECTION)
			lpfc_prot_mask |= SHOST_DIF_TYPE1_PROTECTION;

		if (lpfc_prot_mask && lpfc_prot_guard) {
			if ((old_mask != lpfc_prot_mask) ||
				(old_guard != lpfc_prot_guard))
				lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
					"1475 Registering BlockGuard with the "
					"SCSI layer: mask %d  guard %d\n",
					lpfc_prot_mask, lpfc_prot_guard);

			scsi_host_set_prot(shost, lpfc_prot_mask);
			scsi_host_set_guard(shost, lpfc_prot_guard);
		} else
			lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"1479 Not Registering BlockGuard with the SCSI "
				"layer, Bad protection parameters: %d %d\n",
				old_mask, old_guard);
	}

	if (!_dump_buf_data) {
		while (pagecnt) {
			spin_lock_init(&_dump_buf_lock);
			_dump_buf_data =
				(char *) __get_free_pages(GFP_KERNEL, pagecnt);
			if (_dump_buf_data) {
				lpfc_printf_log(phba, KERN_ERR, LOG_BG,
					"9043 BLKGRD: allocated %d pages for "
				       "_dump_buf_data at 0x%p\n",
				       (1 << pagecnt), _dump_buf_data);
				_dump_buf_data_order = pagecnt;
				memset(_dump_buf_data, 0,
				       ((1 << PAGE_SHIFT) << pagecnt));
				break;
			} else
				--pagecnt;
		}
		if (!_dump_buf_data_order)
			lpfc_printf_log(phba, KERN_ERR, LOG_BG,
				"9044 BLKGRD: ERROR unable to allocate "
			       "memory for hexdump\n");
	} else
		lpfc_printf_log(phba, KERN_ERR, LOG_BG,
			"9045 BLKGRD: already allocated _dump_buf_data=0x%p"
		       "\n", _dump_buf_data);
	if (!_dump_buf_dif) {
		while (pagecnt) {
			_dump_buf_dif =
				(char *) __get_free_pages(GFP_KERNEL, pagecnt);
			if (_dump_buf_dif) {
				lpfc_printf_log(phba, KERN_ERR, LOG_BG,
					"9046 BLKGRD: allocated %d pages for "
				       "_dump_buf_dif at 0x%p\n",
				       (1 << pagecnt), _dump_buf_dif);
				_dump_buf_dif_order = pagecnt;
				memset(_dump_buf_dif, 0,
				       ((1 << PAGE_SHIFT) << pagecnt));
				break;
			} else
				--pagecnt;
		}
		if (!_dump_buf_dif_order)
			lpfc_printf_log(phba, KERN_ERR, LOG_BG,
			"9047 BLKGRD: ERROR unable to allocate "
			       "memory for hexdump\n");
	} else
		lpfc_printf_log(phba, KERN_ERR, LOG_BG,
			"9048 BLKGRD: already allocated _dump_buf_dif=0x%p\n",
		       _dump_buf_dif);
}