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
struct file {int dummy; } ;
struct cx88_core {int /*<<< orphan*/  lock; } ;
struct cx8802_fh {TYPE_1__* dev; } ;
struct TYPE_2__ {struct cx88_core* core; } ;

/* Variables and functions */
 int /*<<< orphan*/  cx88_set_tvnorm (struct cx88_core*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vidioc_s_std (struct file *file, void *priv, v4l2_std_id *id)
{
	struct cx88_core  *core = ((struct cx8802_fh *)priv)->dev->core;

	mutex_lock(&core->lock);
	cx88_set_tvnorm(core,*id);
	mutex_unlock(&core->lock);
	return 0;
}