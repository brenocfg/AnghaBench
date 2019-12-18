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
struct lbs_private {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_802_11_PS_MODE ; 
 int /*<<< orphan*/  CMD_SUBCMD_EXIT_PS ; 
 int /*<<< orphan*/  LBS802_11POWERMODECAM ; 
 int /*<<< orphan*/  LBS_DEB_HOST ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_prepare_and_send_command (struct lbs_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void lbs_ps_wakeup(struct lbs_private *priv, int wait_option)
{
	__le32 Localpsmode;

	lbs_deb_enter(LBS_DEB_HOST);

	Localpsmode = cpu_to_le32(LBS802_11POWERMODECAM);

	lbs_prepare_and_send_command(priv, CMD_802_11_PS_MODE,
			      CMD_SUBCMD_EXIT_PS,
			      wait_option, 0, &Localpsmode);

	lbs_deb_leave(LBS_DEB_HOST);
}