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
struct v4l2_audio {scalar_t__ mode; int /*<<< orphan*/  name; int /*<<< orphan*/  capability; scalar_t__ index; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_AUDCAP_STEREO ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int vidioc_g_audio(struct file *file, void *fh, struct v4l2_audio *a)
{
	a->index = 0;
	a->capability = V4L2_AUDCAP_STEREO;
	strcpy(a->name, "USB audio in");
	a->mode = 0;
	return 0;
}