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
typedef  scalar_t__ u32 ;
struct lbs_private {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  LBS_DEB_CMD ; 
 scalar_t__ MACREG_INT_CODE_MIC_ERR_UNICAST ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_send_iwevcustom_event (struct lbs_private*,char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 

__attribute__((used)) static void handle_mic_failureevent(struct lbs_private *priv, u32 event)
{
	char buf[50];

	lbs_deb_enter(LBS_DEB_CMD);
	memset(buf, 0, sizeof(buf));

	sprintf(buf, "%s", "MLME-MICHAELMICFAILURE.indication ");

	if (event == MACREG_INT_CODE_MIC_ERR_UNICAST) {
		strcat(buf, "unicast ");
	} else {
		strcat(buf, "multicast ");
	}

	lbs_send_iwevcustom_event(priv, buf);
	lbs_deb_leave(LBS_DEB_CMD);
}