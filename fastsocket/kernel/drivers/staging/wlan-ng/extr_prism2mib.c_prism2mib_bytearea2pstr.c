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
typedef  int /*<<< orphan*/  wlandevice_t ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  p80211pstrd_t ;
typedef  int /*<<< orphan*/  p80211msg_dot11req_mibset_t ;
struct TYPE_3__ {int /*<<< orphan*/  parm2; int /*<<< orphan*/  parm1; } ;
typedef  TYPE_1__ mibrec_t ;
typedef  int /*<<< orphan*/  hfa384x_t ;

/* Variables and functions */
 int MIB_TMP_MAXLEN ; 
 int hfa384x_drvr_getconfig (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hfa384x_drvr_setconfig (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prism2mgmt_bytearea2pstr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prism2mgmt_pstr2bytearea (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int prism2mib_bytearea2pstr(mibrec_t *mib,
				   int isget,
				   wlandevice_t *wlandev,
				   hfa384x_t *hw,
				   p80211msg_dot11req_mibset_t *msg,
				   void *data)
{
	int result;
	p80211pstrd_t *pstr = (p80211pstrd_t *) data;
	u8 bytebuf[MIB_TMP_MAXLEN];

	if (isget) {
		result =
		    hfa384x_drvr_getconfig(hw, mib->parm1, bytebuf, mib->parm2);
		prism2mgmt_bytearea2pstr(bytebuf, pstr, mib->parm2);
	} else {
		memset(bytebuf, 0, mib->parm2);
		prism2mgmt_pstr2bytearea(bytebuf, pstr);
		result =
		    hfa384x_drvr_setconfig(hw, mib->parm1, bytebuf, mib->parm2);
	}

	return result;
}