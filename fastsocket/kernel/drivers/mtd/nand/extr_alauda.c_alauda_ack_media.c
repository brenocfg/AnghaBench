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
struct alauda {int /*<<< orphan*/  card_mutex; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALAUDA_ACK_XD_MEDIA_CHANGE ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alauda_ack_media(struct alauda *al)
{
	int ret;

	mutex_lock(&al->card_mutex);
	ret = usb_control_msg(al->dev, usb_sndctrlpipe(al->dev, 0),
			ALAUDA_ACK_XD_MEDIA_CHANGE, 0x40, 0, 1, NULL, 0, HZ);
	mutex_unlock(&al->card_mutex);
	return ret;
}