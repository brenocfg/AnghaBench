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
struct qeth_card {TYPE_1__* gdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int EIO ; 
 int EPERM ; 
 int /*<<< orphan*/  QETH_DBF_CTRL_LEN ; 
 int /*<<< orphan*/  QETH_DBF_HEX (int /*<<< orphan*/ ,int,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QETH_DBF_MESSAGE (int,char*,unsigned char,char*) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT_ (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int qeth_check_idx_response(struct qeth_card *card,
	unsigned char *buffer)
{
	if (!buffer)
		return 0;

	QETH_DBF_HEX(CTRL, 2, buffer, QETH_DBF_CTRL_LEN);
	if ((buffer[2] & 0xc0) == 0xc0) {
		QETH_DBF_MESSAGE(2, "received an IDX TERMINATE "
			   "with cause code 0x%02x%s\n",
			   buffer[4],
			   ((buffer[4] == 0x22) ?
			    " -- try another portname" : ""));
		QETH_DBF_TEXT(TRACE, 2, "ckidxres");
		QETH_DBF_TEXT(TRACE, 2, " idxterm");
		QETH_DBF_TEXT_(TRACE, 2, "  rc%d", -EIO);
		if (buffer[4] == 0xf6) {
			dev_err(&card->gdev->dev,
			"The qeth device is not configured "
			"for the OSI layer required by z/VM\n");
			return -EPERM;
		}
		return -EIO;
	}
	return 0;
}