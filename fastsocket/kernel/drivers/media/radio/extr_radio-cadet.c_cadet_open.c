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
struct file {int dummy; } ;
struct cadet {int users; int /*<<< orphan*/  read_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct cadet* video_drvdata (struct file*) ; 

__attribute__((used)) static int cadet_open(struct file *file)
{
	struct cadet *dev = video_drvdata(file);

	dev->users++;
	if (1 == dev->users)
		init_waitqueue_head(&dev->read_queue);
	return 0;
}