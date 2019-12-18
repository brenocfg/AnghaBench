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
struct mxb {int /*<<< orphan*/  tea6420_2; int /*<<< orphan*/  tea6420_1; } ;
struct TYPE_2__ {int /*<<< orphan*/  output; int /*<<< orphan*/  input; } ;

/* Variables and functions */
 TYPE_1__** TEA6420_line ; 
 int /*<<< orphan*/  audio ; 
 int /*<<< orphan*/  s_routing ; 
 int /*<<< orphan*/  v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void tea6420_route_line(struct mxb *mxb, int idx)
{
	v4l2_subdev_call(mxb->tea6420_1, audio, s_routing,
		TEA6420_line[idx][0].input, TEA6420_line[idx][0].output, 0);
	v4l2_subdev_call(mxb->tea6420_2, audio, s_routing,
		TEA6420_line[idx][1].input, TEA6420_line[idx][1].output, 0);
}