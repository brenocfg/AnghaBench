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
struct video_card {int /*<<< orphan*/  fasync; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int fasync_helper (int,struct file*,int,int /*<<< orphan*/ *) ; 
 struct video_card* file_to_video_card (struct file*) ; 

__attribute__((used)) static int dv1394_fasync(int fd, struct file *file, int on)
{
	/* I just copied this code verbatim from Alan Cox's mouse driver example
	   (Documentation/DocBook/) */

	struct video_card *video = file_to_video_card(file);

	return fasync_helper(fd, file, on, &video->fasync);
}