#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wlandevice_t ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_5__ {int len; } ;
typedef  TYPE_1__ p80211pstrd_t ;
typedef  int /*<<< orphan*/  p80211msg_dot11req_mibset_t ;
struct TYPE_6__ {int /*<<< orphan*/  parm1; } ;
typedef  TYPE_2__ mibrec_t ;
typedef  int /*<<< orphan*/  hfa384x_t ;

/* Variables and functions */
 int /*<<< orphan*/  HFA384x_RID_CNFWEP128DEFAULTKEY_LEN ; 
 int /*<<< orphan*/  HFA384x_RID_CNFWEPDEFAULTKEY_LEN ; 
 int MIB_TMP_MAXLEN ; 
 int hfa384x_drvr_setconfig (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prism2mgmt_pstr2bytearea (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int prism2mib_wepdefaultkey(mibrec_t *mib,
				   int isget,
				   wlandevice_t *wlandev,
				   hfa384x_t *hw,
				   p80211msg_dot11req_mibset_t *msg,
				   void *data)
{
	int result;
	p80211pstrd_t *pstr = (p80211pstrd_t *) data;
	u8 bytebuf[MIB_TMP_MAXLEN];
	u16 len;

	if (isget) {
		result = 0;	/* Should never happen. */
	} else {
		len = (pstr->len > 5) ? HFA384x_RID_CNFWEP128DEFAULTKEY_LEN :
		    HFA384x_RID_CNFWEPDEFAULTKEY_LEN;
		memset(bytebuf, 0, len);
		prism2mgmt_pstr2bytearea(bytebuf, pstr);
		result = hfa384x_drvr_setconfig(hw, mib->parm1, bytebuf, len);
	}

	return result;
}