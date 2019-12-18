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
typedef  int uint8_t ;
struct beiscsi_hba {int dummy; } ;
struct be_mcc_wrb {int dummy; } ;
struct be_cmd_get_boot_target_resp {unsigned int boot_session_handle; int /*<<< orphan*/  boot_session_count; } ;

/* Variables and functions */
 int BEISCSI_LOG_CONFIG ; 
 int BEISCSI_LOG_INIT ; 
 int /*<<< orphan*/  BE_REOPEN_BOOT_SESSIONS ; 
 int EAGAIN ; 
 int EBUSY ; 
 int ENXIO ; 
 unsigned int INVALID_SESS_HANDLE ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int,char*) ; 
 int beiscsi_mccq_compl (struct beiscsi_hba*,unsigned int,struct be_mcc_wrb**,int /*<<< orphan*/ *) ; 
 struct be_cmd_get_boot_target_resp* embedded_payload (struct be_mcc_wrb*) ; 
 unsigned int mgmt_get_boot_target (struct beiscsi_hba*) ; 
 unsigned int mgmt_reopen_session (struct beiscsi_hba*,int /*<<< orphan*/ ,unsigned int) ; 

int be_mgmt_get_boot_shandle(struct beiscsi_hba *phba,
			      unsigned int *s_handle)
{
	struct be_cmd_get_boot_target_resp *boot_resp;
	struct be_mcc_wrb *wrb;
	unsigned int tag;
	uint8_t boot_retry = 3;
	int rc;

	do {
		/* Get the Boot Target Session Handle and Count*/
		tag = mgmt_get_boot_target(phba);
		if (!tag) {
			beiscsi_log(phba, KERN_ERR,
				    BEISCSI_LOG_CONFIG | BEISCSI_LOG_INIT,
				    "BG_%d : Getting Boot Target Info Failed\n");
			return -EAGAIN;
		}

		rc = beiscsi_mccq_compl(phba, tag, &wrb, NULL);
		if (rc) {
			beiscsi_log(phba, KERN_ERR,
				    BEISCSI_LOG_INIT | BEISCSI_LOG_CONFIG,
				    "BG_%d : MBX CMD get_boot_target Failed\n");
			return -EBUSY;
		}

		boot_resp = embedded_payload(wrb);

		/* Check if the there are any Boot targets configured */
		if (!boot_resp->boot_session_count) {
			beiscsi_log(phba, KERN_INFO,
				    BEISCSI_LOG_INIT | BEISCSI_LOG_CONFIG,
				    "BG_%d  ;No boot targets configured\n");
			return -ENXIO;
		}

		/* FW returns the session handle of the boot session */
		if (boot_resp->boot_session_handle != INVALID_SESS_HANDLE) {
			*s_handle = boot_resp->boot_session_handle;
			return 0;
		}

		/* Issue MBX Cmd to FW to login to the boot target */
		tag = mgmt_reopen_session(phba, BE_REOPEN_BOOT_SESSIONS,
					  INVALID_SESS_HANDLE);
		if (!tag) {
			beiscsi_log(phba, KERN_ERR,
				    BEISCSI_LOG_INIT | BEISCSI_LOG_CONFIG,
				    "BG_%d : mgmt_reopen_session Failed\n");
			return -EAGAIN;
		}

		rc = beiscsi_mccq_compl(phba, tag, NULL, NULL);
		if (rc) {
			beiscsi_log(phba, KERN_ERR,
				    BEISCSI_LOG_INIT | BEISCSI_LOG_CONFIG,
				    "BG_%d : mgmt_reopen_session Failed");
			return rc;
		}
	} while (--boot_retry);

	/* Couldn't log into the boot target */
	beiscsi_log(phba, KERN_ERR,
		    BEISCSI_LOG_INIT | BEISCSI_LOG_CONFIG,
		    "BG_%d : Login to Boot Target Failed\n");
	return -ENXIO;
}