#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int hostwep; } ;
typedef  TYPE_1__ wlandevice_t ;
typedef  int /*<<< orphan*/  p80211msg_dot11req_mibset_t ;
struct TYPE_8__ {int /*<<< orphan*/  parm2; } ;
typedef  TYPE_2__ mibrec_t ;
typedef  int /*<<< orphan*/  hfa384x_t ;

/* Variables and functions */
 int /*<<< orphan*/  HFA384x_WEPFLAGS_DISABLE_RXCRYPT ; 
 int /*<<< orphan*/  HFA384x_WEPFLAGS_DISABLE_TXCRYPT ; 
 int HOSTWEP_DECRYPT ; 
 int HOSTWEP_ENCRYPT ; 
 int prism2mib_flag (TYPE_2__*,int,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static int prism2mib_privacyinvoked(mibrec_t *mib,
				    int isget,
				    wlandevice_t *wlandev,
				    hfa384x_t *hw,
				    p80211msg_dot11req_mibset_t *msg,
				    void *data)
{
	int result;

	if (wlandev->hostwep & HOSTWEP_DECRYPT) {
		if (wlandev->hostwep & HOSTWEP_DECRYPT)
			mib->parm2 |= HFA384x_WEPFLAGS_DISABLE_RXCRYPT;
		if (wlandev->hostwep & HOSTWEP_ENCRYPT)
			mib->parm2 |= HFA384x_WEPFLAGS_DISABLE_TXCRYPT;
	}

	result = prism2mib_flag(mib, isget, wlandev, hw, msg, data);

	return result;
}