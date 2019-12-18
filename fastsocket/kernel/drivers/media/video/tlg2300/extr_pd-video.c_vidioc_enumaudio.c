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
struct v4l2_audio {scalar_t__ index; scalar_t__ mode; int /*<<< orphan*/  name; int /*<<< orphan*/  capability; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_AUDCAP_STEREO ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int vidioc_enumaudio(struct file *file, void *fh, struct v4l2_audio *a)
{
	if (0 != a->index)
		return -EINVAL;
	a->capability = V4L2_AUDCAP_STEREO;
	strcpy(a->name, "USB audio in");
	/*Poseidon have no AVL function.*/
	a->mode = 0;
	return 0;
}