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
struct tty_struct {TYPE_1__* ops; } ;
struct sirtty_cb {scalar_t__ magic; struct tty_struct* tty; } ;
struct sir_dev {struct sirtty_cb* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* stop ) (struct tty_struct*) ;} ;

/* Variables and functions */
 int ESTALE ; 
 scalar_t__ IRTTY_MAGIC ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  irtty_mutex ; 
 int /*<<< orphan*/  irtty_stop_receiver (struct tty_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct tty_struct*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int irtty_stop_dev(struct sir_dev *dev)
{
	struct sirtty_cb *priv;
	struct tty_struct *tty;

	/* serialize with ldisc open/close */
	mutex_lock(&irtty_mutex);

	priv = dev->priv;
	if (unlikely(!priv || priv->magic!=IRTTY_MAGIC)) {
		mutex_unlock(&irtty_mutex);
		return -ESTALE;
	}

	tty = priv->tty;

	/* Make sure we don't receive more data */
	irtty_stop_receiver(tty, TRUE);
	if (tty->ops->stop)
		tty->ops->stop(tty);

	mutex_unlock(&irtty_mutex);

	return 0;
}