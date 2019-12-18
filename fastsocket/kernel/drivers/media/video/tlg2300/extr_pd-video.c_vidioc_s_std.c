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
typedef  int /*<<< orphan*/  v4l2_std_id ;
struct front_face {int /*<<< orphan*/  pd; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  logs (struct front_face*) ; 
 int set_std (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vidioc_s_std(struct file *file, void *fh, v4l2_std_id *norm)
{
	struct front_face *front = fh;
	logs(front);
	return set_std(front->pd, norm);
}