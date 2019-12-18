#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {struct snd_soc_codec* disc_data; TYPE_1__* ops; } ;
struct snd_soc_codec {int dummy; } ;
struct TYPE_2__ {int (* write ) (struct tty_struct*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 struct snd_soc_codec* cx20442_codec ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int stub1 (struct tty_struct*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v253_init ; 

__attribute__((used)) static int v253_open(struct tty_struct *tty)
{
	struct snd_soc_codec *codec = cx20442_codec;
	int ret, len = strlen(v253_init);

	/* Doesn't make sense without write callback */
	if (!tty->ops->write)
		return -EINVAL;

	/* Pass the codec structure address for use by other ldisc callbacks */
	tty->disc_data = codec;

	if (tty->ops->write(tty, v253_init, len) != len) {
		ret = -EIO;
		goto err;
	}
	/* Actual setup will be performed after the modem responds. */
	return 0;
err:
	tty->disc_data = NULL;
	return ret;
}