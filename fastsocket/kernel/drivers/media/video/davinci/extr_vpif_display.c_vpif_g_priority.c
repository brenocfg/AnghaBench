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
struct vpif_fh {struct channel_obj* channel; } ;
struct file {int dummy; } ;
struct channel_obj {int /*<<< orphan*/  prio; } ;
typedef  enum v4l2_priority { ____Placeholder_v4l2_priority } v4l2_priority ;

/* Variables and functions */
 int v4l2_prio_max (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vpif_g_priority(struct file *file, void *priv, enum v4l2_priority *p)
{
	struct vpif_fh *fh = priv;
	struct channel_obj *ch = fh->channel;

	*p = v4l2_prio_max(&ch->prio);

	return 0;
}