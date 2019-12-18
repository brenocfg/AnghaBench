#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned char u8 ;
struct se_device {int dummy; } ;
struct se_cmd {char* t_task_cdb; int data_length; struct se_device* se_dev; } ;
typedef  int sense_reason_t ;
struct TYPE_3__ {unsigned char page; unsigned char subpage; int (* emulate ) (struct se_device*,int /*<<< orphan*/ ,unsigned char*) ;} ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  GOOD ; 
 char MODE_SELECT_10 ; 
 int SE_MODE_PAGE_BUF ; 
 int TCM_INVALID_CDB_FIELD ; 
 int TCM_INVALID_PARAMETER_LIST ; 
 int TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE ; 
 int TCM_PARAMETER_LIST_LENGTH_ERROR ; 
 int TCM_UNKNOWN_MODE_PAGE ; 
 scalar_t__ memcmp (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* modesense_handlers ; 
 int stub1 (struct se_device*,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  target_complete_cmd (struct se_cmd*,int /*<<< orphan*/ ) ; 
 unsigned char* transport_kmap_data_sg (struct se_cmd*) ; 
 int /*<<< orphan*/  transport_kunmap_data_sg (struct se_cmd*) ; 

__attribute__((used)) static sense_reason_t spc_emulate_modeselect(struct se_cmd *cmd)
{
	struct se_device *dev = cmd->se_dev;
	char *cdb = cmd->t_task_cdb;
	bool ten = cdb[0] == MODE_SELECT_10;
	int off = ten ? 8 : 4;
	bool pf = !!(cdb[1] & 0x10);
	u8 page, subpage;
	unsigned char *buf;
	unsigned char tbuf[SE_MODE_PAGE_BUF];
	int length;
	int ret = 0;
	int i;

	if (!cmd->data_length) {
		target_complete_cmd(cmd, GOOD);
		return 0;
	}

	if (cmd->data_length < off + 2)
		return TCM_PARAMETER_LIST_LENGTH_ERROR;

	buf = transport_kmap_data_sg(cmd);
	if (!buf)
		return TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;

	if (!pf) {
		ret = TCM_INVALID_CDB_FIELD;
		goto out;
	}

	page = buf[off] & 0x3f;
	subpage = buf[off] & 0x40 ? buf[off + 1] : 0;

	for (i = 0; i < ARRAY_SIZE(modesense_handlers); ++i)
		if (modesense_handlers[i].page == page &&
		    modesense_handlers[i].subpage == subpage) {
			memset(tbuf, 0, SE_MODE_PAGE_BUF);
			length = modesense_handlers[i].emulate(dev, 0, tbuf);
			goto check_contents;
		}

	ret = TCM_UNKNOWN_MODE_PAGE;
	goto out;

check_contents:
	if (cmd->data_length < off + length) {
		ret = TCM_PARAMETER_LIST_LENGTH_ERROR;
		goto out;
	}

	if (memcmp(buf + off, tbuf, length))
		ret = TCM_INVALID_PARAMETER_LIST;

out:
	transport_kunmap_data_sg(cmd);

	if (!ret)
		target_complete_cmd(cmd, GOOD);
	return ret;
}