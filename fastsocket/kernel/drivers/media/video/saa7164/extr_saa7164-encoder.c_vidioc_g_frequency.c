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
struct v4l2_frequency {int /*<<< orphan*/  frequency; int /*<<< orphan*/  type; } ;
struct saa7164_port {int /*<<< orphan*/  freq; } ;
struct saa7164_encoder_fh {struct saa7164_port* port; } ;
struct file {struct saa7164_encoder_fh* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_TUNER_ANALOG_TV ; 

__attribute__((used)) static int vidioc_g_frequency(struct file *file, void *priv,
	struct v4l2_frequency *f)
{
	struct saa7164_encoder_fh *fh = file->private_data;
	struct saa7164_port *port = fh->port;

	f->type = V4L2_TUNER_ANALOG_TV;
	f->frequency = port->freq;

	return 0;
}