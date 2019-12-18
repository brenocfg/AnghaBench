#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_control {int /*<<< orphan*/  value; int /*<<< orphan*/  id; } ;
struct cx88_core {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  default_value; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {TYPE_1__ v; } ;

/* Variables and functions */
 int CX8800_CTLS ; 
 TYPE_2__* cx8800_ctls ; 
 int /*<<< orphan*/  cx88_set_control (struct cx88_core*,struct v4l2_control*) ; 

__attribute__((used)) static void init_controls(struct cx88_core *core)
{
	struct v4l2_control ctrl;
	int i;

	for (i = 0; i < CX8800_CTLS; i++) {
		ctrl.id=cx8800_ctls[i].v.id;
		ctrl.value=cx8800_ctls[i].v.default_value;

		cx88_set_control(core, &ctrl);
	}
}