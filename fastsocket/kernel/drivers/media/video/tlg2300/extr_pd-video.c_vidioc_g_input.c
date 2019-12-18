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
struct running_context {unsigned int sig_index; } ;
struct TYPE_2__ {struct running_context context; } ;
struct poseidon {TYPE_1__ video_data; } ;
struct front_face {struct poseidon* pd; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  logs (struct front_face*) ; 

__attribute__((used)) static int vidioc_g_input(struct file *file, void *fh, unsigned int *i)
{
	struct front_face *front = fh;
	struct poseidon *pd = front->pd;
	struct running_context *context = &pd->video_data.context;

	logs(front);
	*i = context->sig_index;
	return 0;
}