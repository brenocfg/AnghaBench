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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct lbs_private {scalar_t__ card; } ;
struct if_cs_card {int dummy; } ;

/* Variables and functions */
 int IF_CS_BIT_COMMAND ; 
 int /*<<< orphan*/  IF_CS_CARD_STATUS ; 
 int /*<<< orphan*/  IF_CS_CMD ; 
 int /*<<< orphan*/  IF_CS_CMD_LEN ; 
 int /*<<< orphan*/  IF_CS_HOST_INT_CAUSE ; 
 int /*<<< orphan*/  IF_CS_HOST_STATUS ; 
 int /*<<< orphan*/  LBS_DEB_CS ; 
 int /*<<< orphan*/  if_cs_disable_ints (struct if_cs_card*) ; 
 int /*<<< orphan*/  if_cs_enable_ints (struct if_cs_card*) ; 
 int if_cs_read16 (struct if_cs_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_cs_write16 (struct if_cs_card*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_cs_write16_rep (struct if_cs_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  if_cs_write8 (struct if_cs_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lbs_pr_err (char*) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int if_cs_send_cmd(struct lbs_private *priv, u8 *buf, u16 nb)
{
	struct if_cs_card *card = (struct if_cs_card *)priv->card;
	int ret = -1;
	int loops = 0;

	lbs_deb_enter(LBS_DEB_CS);
	if_cs_disable_ints(card);

	/* Is hardware ready? */
	while (1) {
		u16 status = if_cs_read16(card, IF_CS_CARD_STATUS);
		if (status & IF_CS_BIT_COMMAND)
			break;
		if (++loops > 100) {
			lbs_pr_err("card not ready for commands\n");
			goto done;
		}
		mdelay(1);
	}

	if_cs_write16(card, IF_CS_CMD_LEN, nb);

	if_cs_write16_rep(card, IF_CS_CMD, buf, nb / 2);
	/* Are we supposed to transfer an odd amount of bytes? */
	if (nb & 1)
		if_cs_write8(card, IF_CS_CMD, buf[nb-1]);

	/* "Assert the download over interrupt command in the Host
	 * status register" */
	if_cs_write16(card, IF_CS_HOST_STATUS, IF_CS_BIT_COMMAND);

	/* "Assert the download over interrupt command in the Card
	 * interrupt case register" */
	if_cs_write16(card, IF_CS_HOST_INT_CAUSE, IF_CS_BIT_COMMAND);
	ret = 0;

done:
	if_cs_enable_ints(card);
	lbs_deb_leave_args(LBS_DEB_CS, "ret %d", ret);
	return ret;
}