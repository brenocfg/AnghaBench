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
struct video_card {int /*<<< orphan*/  open; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_dv1394_shutdown (struct video_card*,int) ; 
 struct video_card* file_to_video_card (struct file*) ; 

__attribute__((used)) static int dv1394_release(struct inode *inode, struct file *file)
{
	struct video_card *video = file_to_video_card(file);

	/* OK to free the DMA buffer, no more mappings can exist */
	do_dv1394_shutdown(video, 1);

	/* give someone else a turn */
	clear_bit(0, &video->open);

	return 0;
}