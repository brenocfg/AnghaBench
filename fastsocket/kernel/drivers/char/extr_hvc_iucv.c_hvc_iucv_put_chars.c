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
 int hvc_iucv_queue (struct hvc_iucv_private*,char const*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hvc_iucv_put_chars(uint32_t vtermno, const char *buf, int count)
{
	struct hvc_iucv_private *priv = hvc_iucv_get_private(vtermno);
	int queued;

	if (count <= 0)
		return 0;

	if (!priv)
		return -ENODEV;

	spin_lock(&priv->lock);
	queued = hvc_iucv_queue(priv, buf, count);
	spin_unlock(&priv->lock);

	return queued;
}