#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ wlandevice_t ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_14__ {int /*<<< orphan*/  buf; } ;
typedef  TYPE_4__ pda_t ;
struct TYPE_12__ {int /*<<< orphan*/  data; void* status; int /*<<< orphan*/  len; int /*<<< orphan*/  did; } ;
struct TYPE_11__ {int len; scalar_t__ data; void* status; int /*<<< orphan*/  did; } ;
struct TYPE_15__ {int msglen; TYPE_2__ pda; TYPE_1__ resultcode; int /*<<< orphan*/  devname; int /*<<< orphan*/  msgcode; } ;
typedef  TYPE_5__ p80211msg_p2req_readpda_t ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  DIDmsg_p2req_readpda ; 
 int /*<<< orphan*/  DIDmsg_p2req_readpda_pda ; 
 int /*<<< orphan*/  DIDmsg_p2req_readpda_resultcode ; 
 int /*<<< orphan*/  HFA384x_PDA_LEN_MAX ; 
 void* P80211ENUM_msgitem_status_no_value ; 
 scalar_t__ P80211ENUM_resultcode_success ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mkpdrlist (TYPE_4__*) ; 
 scalar_t__ prism2mgmt_readpda (TYPE_3__*,TYPE_5__*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int read_cardpda(pda_t *pda, wlandevice_t *wlandev)
{
	int result = 0;
	p80211msg_p2req_readpda_t msg;

	/* set up the msg */
	msg.msgcode = DIDmsg_p2req_readpda;
	msg.msglen = sizeof(msg);
	strcpy(msg.devname, wlandev->name);
	msg.pda.did = DIDmsg_p2req_readpda_pda;
	msg.pda.len = HFA384x_PDA_LEN_MAX;
	msg.pda.status = P80211ENUM_msgitem_status_no_value;
	msg.resultcode.did = DIDmsg_p2req_readpda_resultcode;
	msg.resultcode.len = sizeof(u32);
	msg.resultcode.status = P80211ENUM_msgitem_status_no_value;

	if (prism2mgmt_readpda(wlandev, &msg) != 0) {
		/* prism2mgmt_readpda prints an errno if appropriate */
		result = -1;
	} else if (msg.resultcode.data == P80211ENUM_resultcode_success) {
		memcpy(pda->buf, msg.pda.data, HFA384x_PDA_LEN_MAX);
		result = mkpdrlist(pda);
	} else {
		/* resultcode must've been something other than success */
		result = -1;
	}

	return result;
}