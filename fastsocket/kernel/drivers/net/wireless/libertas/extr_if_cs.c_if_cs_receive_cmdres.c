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
typedef  int u32 ;
typedef  int u16 ;
struct lbs_private {int /*<<< orphan*/  driver_lock; int /*<<< orphan*/  dnld_sent; int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  DNLD_RES_RECEIVED ; 
 int IF_CS_BIT_RESP ; 
 int /*<<< orphan*/  IF_CS_CARD_STATUS ; 
 int /*<<< orphan*/  IF_CS_RESP ; 
 int /*<<< orphan*/  IF_CS_RESP_LEN ; 
 int LBS_CMD_BUFFER_SIZE ; 
 int /*<<< orphan*/  LBS_DEB_CS ; 
 void* if_cs_read16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_cs_read16_rep (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  if_cs_read8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  lbs_pr_err (char*,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int if_cs_receive_cmdres(struct lbs_private *priv, u8 *data, u32 *len)
{
	unsigned long flags;
	int ret = -1;
	u16 status;

	lbs_deb_enter(LBS_DEB_CS);

	/* is hardware ready? */
	status = if_cs_read16(priv->card, IF_CS_CARD_STATUS);
	if ((status & IF_CS_BIT_RESP) == 0) {
		lbs_pr_err("no cmd response in card\n");
		*len = 0;
		goto out;
	}

	*len = if_cs_read16(priv->card, IF_CS_RESP_LEN);
	if ((*len == 0) || (*len > LBS_CMD_BUFFER_SIZE)) {
		lbs_pr_err("card cmd buffer has invalid # of bytes (%d)\n", *len);
		goto out;
	}

	/* read even number of bytes, then odd byte if necessary */
	if_cs_read16_rep(priv->card, IF_CS_RESP, data, *len/sizeof(u16));
	if (*len & 1)
		data[*len-1] = if_cs_read8(priv->card, IF_CS_RESP);

	/* This is a workaround for a firmware that reports too much
	 * bytes */
	*len -= 8;
	ret = 0;

	/* Clear this flag again */
	spin_lock_irqsave(&priv->driver_lock, flags);
	priv->dnld_sent = DNLD_RES_RECEIVED;
	spin_unlock_irqrestore(&priv->driver_lock, flags);

out:
	lbs_deb_leave_args(LBS_DEB_CS, "ret %d, len %d", ret, *len);
	return ret;
}