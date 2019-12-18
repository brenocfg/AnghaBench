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
struct hci_conn {scalar_t__ ssp_mode; int link_mode; TYPE_1__* hdev; } ;
struct TYPE_2__ {scalar_t__ ssp_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_conn*) ; 
 int HCI_LM_ENCRYPT ; 

int hci_conn_check_link_mode(struct hci_conn *conn)
{
	BT_DBG("conn %p", conn);

	if (conn->ssp_mode > 0 && conn->hdev->ssp_mode > 0 &&
					!(conn->link_mode & HCI_LM_ENCRYPT))
		return 0;

	return 1;
}