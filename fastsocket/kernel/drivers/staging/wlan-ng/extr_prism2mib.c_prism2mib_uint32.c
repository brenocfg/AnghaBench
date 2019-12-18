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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  p80211msg_dot11req_mibset_t ;
struct TYPE_3__ {int /*<<< orphan*/  parm1; } ;
typedef  TYPE_1__ mibrec_t ;
typedef  int /*<<< orphan*/  hfa384x_t ;

/* Variables and functions */
 int MIB_TMP_MAXLEN ; 
 int hfa384x_drvr_getconfig16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hfa384x_drvr_setconfig16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int prism2mib_uint32(mibrec_t *mib,
			    int isget,
			    wlandevice_t *wlandev,
			    hfa384x_t *hw,
			    p80211msg_dot11req_mibset_t *msg, void *data)
{
	int result;
	u32 *uint32 = (u32 *) data;
	u8 bytebuf[MIB_TMP_MAXLEN];
	u16 *wordbuf = (u16 *) bytebuf;

	if (isget) {
		result = hfa384x_drvr_getconfig16(hw, mib->parm1, wordbuf);
		*uint32 = *wordbuf;
	} else {
		*wordbuf = *uint32;
		result = hfa384x_drvr_setconfig16(hw, mib->parm1, *wordbuf);
	}

	return result;
}