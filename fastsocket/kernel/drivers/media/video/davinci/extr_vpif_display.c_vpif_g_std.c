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
typedef  int /*<<< orphan*/  v4l2_std_id ;
struct vpif_fh {struct channel_obj* channel; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  stdid; } ;
struct channel_obj {TYPE_1__ video; } ;

/* Variables and functions */

__attribute__((used)) static int vpif_g_std(struct file *file, void *priv, v4l2_std_id *std)
{
	struct vpif_fh *fh = priv;
	struct channel_obj *ch = fh->channel;

	*std = ch->video.stdid;
	return 0;
}