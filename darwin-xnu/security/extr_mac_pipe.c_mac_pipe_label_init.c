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
struct pipe {int /*<<< orphan*/  pipe_label; } ;

/* Variables and functions */
 int /*<<< orphan*/  mac_pipe_label_alloc () ; 

void
mac_pipe_label_init(struct pipe *cpipe)
{

	cpipe->pipe_label = mac_pipe_label_alloc();
}