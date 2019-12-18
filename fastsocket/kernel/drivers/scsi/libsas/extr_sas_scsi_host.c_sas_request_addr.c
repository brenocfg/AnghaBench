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
typedef  int /*<<< orphan*/  u8 ;
struct firmware {scalar_t__ size; int /*<<< orphan*/  data; } ;
struct Scsi_Host {int /*<<< orphan*/  shost_gendev; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ SAS_STRING_ADDR_SIZE ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sas_parse_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int sas_request_addr(struct Scsi_Host *shost, u8 *addr)
{
	int res;
	const struct firmware *fw;

	res = request_firmware(&fw, "sas_addr", &shost->shost_gendev);
	if (res)
		return res;

	if (fw->size < SAS_STRING_ADDR_SIZE) {
		res = -ENODEV;
		goto out;
	}

	sas_parse_addr(addr, fw->data);

out:
	release_firmware(fw);
	return res;
}