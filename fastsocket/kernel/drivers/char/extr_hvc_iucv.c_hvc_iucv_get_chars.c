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
typedef  int /*<<< orphan*/  uint32_t ;
struct hvc_iucv_private {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENODEV ; 
 struct hvc_iucv_private* hvc_iucv_get_private (int /*<<< orphan*/ ) ; 
 int hvc_iucv_write (struct hvc_iucv_private*,char*,int,int*) ; 
 int /*<<< orphan*/  hvc_kick () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hvc_iucv_get_chars(uint32_t vtermno, char *buf, int count)
{
	struct hvc_iucv_private *priv = hvc_iucv_get_private(vtermno);
	int written;
	int has_more_data;

	if (count <= 0)
		return 0;

	if (!priv)
		return -ENODEV;

	spin_lock(&priv->lock);
	has_more_data = 0;
	written = hvc_iucv_write(priv, buf, count, &has_more_data);
	spin_unlock(&priv->lock);

	/* if there are still messages on the queue... schedule another run */
	if (has_more_data)
		hvc_kick();

	return written;
}