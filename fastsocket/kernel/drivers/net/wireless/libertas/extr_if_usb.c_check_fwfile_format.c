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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct fwheader {int /*<<< orphan*/  datalength; int /*<<< orphan*/  dnldcmd; } ;

/* Variables and functions */
#define  FW_HAS_DATA_TO_RECV 129 
#define  FW_HAS_LAST_BLOCK 128 
 int /*<<< orphan*/  lbs_deb_fw (char*) ; 
 int /*<<< orphan*/  lbs_pr_err (char*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_fwfile_format(const uint8_t *data, uint32_t totlen)
{
	uint32_t bincmd, exit;
	uint32_t blksize, offset, len;
	int ret;

	ret = 1;
	exit = len = 0;

	do {
		struct fwheader *fwh = (void *)data;

		bincmd = le32_to_cpu(fwh->dnldcmd);
		blksize = le32_to_cpu(fwh->datalength);
		switch (bincmd) {
		case FW_HAS_DATA_TO_RECV:
			offset = sizeof(struct fwheader) + blksize;
			data += offset;
			len += offset;
			if (len >= totlen)
				exit = 1;
			break;
		case FW_HAS_LAST_BLOCK:
			exit = 1;
			ret = 0;
			break;
		default:
			exit = 1;
			break;
		}
	} while (!exit);

	if (ret)
		lbs_pr_err("firmware file format check FAIL\n");
	else
		lbs_deb_fw("firmware file format check PASS\n");

	return ret;
}