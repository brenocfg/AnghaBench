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
typedef  int /*<<< orphan*/  uint16_t ;
struct scsi_qla_host {int dummy; } ;
struct iscsi_session {int /*<<< orphan*/  password; int /*<<< orphan*/  username; int /*<<< orphan*/  password_in; int /*<<< orphan*/  username_in; struct ddb_entry* dd_data; } ;
struct iscsi_cls_session {struct iscsi_session* dd_data; } ;
struct ddb_entry {struct scsi_qla_host* ha; } ;
typedef  enum iscsi_param { ____Placeholder_iscsi_param } iscsi_param ;

/* Variables and functions */
 int /*<<< orphan*/  BIDI_CHAP ; 
#define  ISCSI_PARAM_CHAP_IN_IDX 129 
#define  ISCSI_PARAM_CHAP_OUT_IDX 128 
 int /*<<< orphan*/  LOCAL_CHAP ; 
 int iscsi_session_get_param (struct iscsi_cls_session*,int,char*) ; 
 int qla4xxx_get_chap_index (struct scsi_qla_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sprintf (char*,char*,...) ; 

__attribute__((used)) static int qla4xxx_session_get_param(struct iscsi_cls_session *cls_sess,
				     enum iscsi_param param, char *buf)
{
	struct iscsi_session *sess = cls_sess->dd_data;
	struct ddb_entry *ddb_entry = sess->dd_data;
	struct scsi_qla_host *ha = ddb_entry->ha;
	int rval, len;
	uint16_t idx;

	switch (param) {
	case ISCSI_PARAM_CHAP_IN_IDX:
		rval = qla4xxx_get_chap_index(ha, sess->username_in,
					      sess->password_in, BIDI_CHAP,
					      &idx);
		if (rval)
			len = sprintf(buf, "\n");
		else
			len = sprintf(buf, "%hu\n", idx);
		break;
	case ISCSI_PARAM_CHAP_OUT_IDX:
		rval = qla4xxx_get_chap_index(ha, sess->username,
					      sess->password, LOCAL_CHAP,
					      &idx);
		if (rval)
			len = sprintf(buf, "\n");
		else
			len = sprintf(buf, "%hu\n", idx);
		break;
	default:
		return iscsi_session_get_param(cls_sess, param, buf);
	}

	return len;
}