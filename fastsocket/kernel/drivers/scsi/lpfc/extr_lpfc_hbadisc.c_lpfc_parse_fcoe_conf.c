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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct lpfc_hba {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FCOE_CONN_TBL_TYPE ; 
 int /*<<< orphan*/  FCOE_PARAM_TYPE ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_INIT ; 
 int /*<<< orphan*/  LPFC_REGION23_SIGNATURE ; 
 scalar_t__ LPFC_REGION23_VERSION ; 
 scalar_t__* lpfc_get_rec_conf23 (scalar_t__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lpfc_read_fcf_conn_tbl (struct lpfc_hba*,scalar_t__*) ; 
 int /*<<< orphan*/  lpfc_read_fcoe_param (struct lpfc_hba*,scalar_t__*) ; 
 scalar_t__ memcmp (scalar_t__*,int /*<<< orphan*/ ,int) ; 

void
lpfc_parse_fcoe_conf(struct lpfc_hba *phba,
		uint8_t *buff,
		uint32_t size)
{
	uint32_t offset = 0, rec_length;
	uint8_t *rec_ptr;

	/*
	 * If data size is less than 2 words signature and version cannot be
	 * verified.
	 */
	if (size < 2*sizeof(uint32_t))
		return;

	/* Check the region signature first */
	if (memcmp(buff, LPFC_REGION23_SIGNATURE, 4)) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
			"2567 Config region 23 has bad signature\n");
		return;
	}

	offset += 4;

	/* Check the data structure version */
	if (buff[offset] != LPFC_REGION23_VERSION) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
			"2568 Config region 23 has bad version\n");
		return;
	}
	offset += 4;

	rec_length = buff[offset + 1];

	/* Read FCoE param record */
	rec_ptr = lpfc_get_rec_conf23(&buff[offset],
			size - offset, FCOE_PARAM_TYPE);
	if (rec_ptr)
		lpfc_read_fcoe_param(phba, rec_ptr);

	/* Read FCF connection table */
	rec_ptr = lpfc_get_rec_conf23(&buff[offset],
		size - offset, FCOE_CONN_TBL_TYPE);
	if (rec_ptr)
		lpfc_read_fcf_conn_tbl(phba, rec_ptr);

}