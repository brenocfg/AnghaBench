#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  v4l2_std_id ;
struct vino_channel_settings {size_t data_norm; } ;
struct file {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  std; } ;
struct TYPE_3__ {int /*<<< orphan*/  input_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,size_t) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct vino_channel_settings* video_drvdata (struct file*) ; 
 TYPE_2__* vino_data_norms ; 
 TYPE_1__* vino_drvdata ; 

__attribute__((used)) static int vino_g_std(struct file *file, void *__fh,
			   v4l2_std_id *std)
{
	struct vino_channel_settings *vcs = video_drvdata(file);
	unsigned long flags;

	spin_lock_irqsave(&vino_drvdata->input_lock, flags);

	*std = vino_data_norms[vcs->data_norm].std;
	dprintk("current standard = %d\n", vcs->data_norm);

	spin_unlock_irqrestore(&vino_drvdata->input_lock, flags);

	return 0;
}