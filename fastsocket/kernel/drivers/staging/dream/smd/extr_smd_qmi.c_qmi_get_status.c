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
struct qmi_msg {int dummy; } ;
typedef  int /*<<< orphan*/  status ;

/* Variables and functions */
 int QMI_RESULT_FAILURE ; 
 scalar_t__ qmi_get_tlv (struct qmi_msg*,int,int,unsigned short*) ; 

__attribute__((used)) static unsigned qmi_get_status(struct qmi_msg *msg, unsigned *error)
{
	unsigned short status[2];
	if (qmi_get_tlv(msg, 0x02, sizeof(status), status)) {
		*error = 0;
		return QMI_RESULT_FAILURE;
	} else {
		*error = status[1];
		return status[0];
	}
}