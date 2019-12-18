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
struct v4l2_tuner {scalar_t__ index; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct file {int dummy; } ;
struct cx88_core {int dummy; } ;
struct cx8800_fh {TYPE_1__* dev; } ;
struct TYPE_2__ {struct cx88_core* core; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_TUNER_RADIO ; 
 int /*<<< orphan*/  call_all (struct cx88_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_tuner*) ; 
 int /*<<< orphan*/  g_tuner ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tuner ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int radio_g_tuner (struct file *file, void *priv,
				struct v4l2_tuner *t)
{
	struct cx88_core  *core = ((struct cx8800_fh *)priv)->dev->core;

	if (unlikely(t->index > 0))
		return -EINVAL;

	strcpy(t->name, "Radio");
	t->type = V4L2_TUNER_RADIO;

	call_all(core, tuner, g_tuner, t);
	return 0;
}