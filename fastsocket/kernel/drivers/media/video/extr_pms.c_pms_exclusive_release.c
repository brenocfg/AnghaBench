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
struct video_device {int dummy; } ;
struct pms_device {int /*<<< orphan*/  in_use; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct video_device* video_devdata (struct file*) ; 

__attribute__((used)) static int pms_exclusive_release(struct file *file)
{
	struct video_device *v = video_devdata(file);
	struct pms_device *pd = (struct pms_device *)v;

	clear_bit(0, &pd->in_use);
	return 0;
}