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
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int AP_DEVICES ; 
 int /*<<< orphan*/  ZCRYPT_CEX2A ; 
 int /*<<< orphan*/  ZCRYPT_CEX2C ; 
 int /*<<< orphan*/  ZCRYPT_CEX3A ; 
 int /*<<< orphan*/  ZCRYPT_CEX3C ; 
 int /*<<< orphan*/  ZCRYPT_PCICA ; 
 int /*<<< orphan*/  ZCRYPT_PCICC ; 
 int /*<<< orphan*/  ZCRYPT_PCIXCC_MCL2 ; 
 int /*<<< orphan*/  ZCRYPT_PCIXCC_MCL3 ; 
 int ZCRYPT_RELEASE ; 
 int ZCRYPT_VARIANT ; 
 int ZCRYPT_VERSION ; 
 int ap_domain_index ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (void*,int,int) ; 
 scalar_t__ sprintf (char*,char*,int,...) ; 
 scalar_t__ sprinthx (char*,char*,unsigned char*,int) ; 
 scalar_t__ sprinthx4 (char*,char*,unsigned int*,int) ; 
 int zcrypt_count_type (int /*<<< orphan*/ ) ; 
 int zcrypt_device_count ; 
 int /*<<< orphan*/  zcrypt_open_count ; 
 int zcrypt_pendingq_count () ; 
 int /*<<< orphan*/  zcrypt_perdev_reqcnt (int*) ; 
 int /*<<< orphan*/  zcrypt_qdepth_mask (unsigned char*) ; 
 int zcrypt_requestq_count () ; 
 int /*<<< orphan*/  zcrypt_status_mask (unsigned char*) ; 

__attribute__((used)) static int zcrypt_status_read(char *resp_buff, char **start, off_t offset,
			      int count, int *eof, void *data)
{
	unsigned char *workarea;
	int len;

	len = 0;

	/* resp_buff is a page. Use the right half for a work area */
	workarea = resp_buff + 2000;
	len += sprintf(resp_buff + len, "\nzcrypt version: %d.%d.%d\n",
		ZCRYPT_VERSION, ZCRYPT_RELEASE, ZCRYPT_VARIANT);
	len += sprintf(resp_buff + len, "Cryptographic domain: %d\n",
		       ap_domain_index);
	len += sprintf(resp_buff + len, "Total device count: %d\n",
		       zcrypt_device_count);
	len += sprintf(resp_buff + len, "PCICA count: %d\n",
		       zcrypt_count_type(ZCRYPT_PCICA));
	len += sprintf(resp_buff + len, "PCICC count: %d\n",
		       zcrypt_count_type(ZCRYPT_PCICC));
	len += sprintf(resp_buff + len, "PCIXCC MCL2 count: %d\n",
		       zcrypt_count_type(ZCRYPT_PCIXCC_MCL2));
	len += sprintf(resp_buff + len, "PCIXCC MCL3 count: %d\n",
		       zcrypt_count_type(ZCRYPT_PCIXCC_MCL3));
	len += sprintf(resp_buff + len, "CEX2C count: %d\n",
		       zcrypt_count_type(ZCRYPT_CEX2C));
	len += sprintf(resp_buff + len, "CEX2A count: %d\n",
		       zcrypt_count_type(ZCRYPT_CEX2A));
	len += sprintf(resp_buff + len, "CEX3C count: %d\n",
		       zcrypt_count_type(ZCRYPT_CEX3C));
	len += sprintf(resp_buff + len, "CEX3A count: %d\n",
		       zcrypt_count_type(ZCRYPT_CEX3A));
	len += sprintf(resp_buff + len, "requestq count: %d\n",
		       zcrypt_requestq_count());
	len += sprintf(resp_buff + len, "pendingq count: %d\n",
		       zcrypt_pendingq_count());
	len += sprintf(resp_buff + len, "Total open handles: %d\n\n",
		       atomic_read(&zcrypt_open_count));
	zcrypt_status_mask(workarea);
	len += sprinthx("Online devices: 1=PCICA 2=PCICC 3=PCIXCC(MCL2) "
			"4=PCIXCC(MCL3) 5=CEX2C 6=CEX2A 7=CEX3C 8=CEX3A",
			resp_buff+len, workarea, AP_DEVICES);
	zcrypt_qdepth_mask(workarea);
	len += sprinthx("Waiting work element counts",
			resp_buff+len, workarea, AP_DEVICES);
	zcrypt_perdev_reqcnt((int *) workarea);
	len += sprinthx4("Per-device successfully completed request counts",
			 resp_buff+len,(unsigned int *) workarea, AP_DEVICES);
	*eof = 1;
	memset((void *) workarea, 0x00, AP_DEVICES * sizeof(unsigned int));
	return len;
}