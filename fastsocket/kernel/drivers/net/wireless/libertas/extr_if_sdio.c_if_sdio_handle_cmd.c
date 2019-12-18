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
typedef  size_t u8 ;
struct lbs_private {scalar_t__ resp_idx; unsigned int* resp_len; int /*<<< orphan*/  driver_lock; int /*<<< orphan*/ * resp_buf; } ;
struct if_sdio_card {struct lbs_private* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (unsigned int) ; 
 int E2BIG ; 
 unsigned int LBS_CMD_BUFFER_SIZE ; 
 int /*<<< orphan*/  LBS_DEB_SDIO ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lbs_deb_sdio (char*,int) ; 
 int /*<<< orphan*/  lbs_notify_command_response (struct lbs_private*,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,size_t*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int if_sdio_handle_cmd(struct if_sdio_card *card,
		u8 *buffer, unsigned size)
{
	struct lbs_private *priv = card->priv;
	int ret;
	unsigned long flags;
	u8 i;

	lbs_deb_enter(LBS_DEB_SDIO);

	if (size > LBS_CMD_BUFFER_SIZE) {
		lbs_deb_sdio("response packet too large (%d bytes)\n",
			(int)size);
		ret = -E2BIG;
		goto out;
	}

	spin_lock_irqsave(&priv->driver_lock, flags);

	i = (priv->resp_idx == 0) ? 1 : 0;
	BUG_ON(priv->resp_len[i]);
	priv->resp_len[i] = size;
	memcpy(priv->resp_buf[i], buffer, size);
	lbs_notify_command_response(priv, i);

	spin_unlock_irqrestore(&card->priv->driver_lock, flags);

	ret = 0;

out:
	lbs_deb_leave_args(LBS_DEB_SDIO, "ret %d", ret);
	return ret;
}