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
struct v4l2_capability {int /*<<< orphan*/  capabilities; int /*<<< orphan*/  version; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct snd_tea575x {scalar_t__ tea5759; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RADIO_VERSION ; 
 int /*<<< orphan*/  V4L2_CAP_TUNER ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 struct snd_tea575x* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_querycap(struct file *file, void  *priv,
					struct v4l2_capability *v)
{
	struct snd_tea575x *tea = video_drvdata(file);

	strcpy(v->card, tea->tea5759 ? "TEA5759" : "TEA5757");
	strlcpy(v->driver, "tea575x-tuner", sizeof(v->driver));
	strlcpy(v->card, "Maestro Radio", sizeof(v->card));
	sprintf(v->bus_info, "PCI");
	v->version = RADIO_VERSION;
	v->capabilities = V4L2_CAP_TUNER;
	return 0;
}