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
struct cx18_open_id {struct cx18* cx; } ;
struct cx18 {int /*<<< orphan*/  prio; } ;
typedef  enum v4l2_priority { ____Placeholder_v4l2_priority } v4l2_priority ;

/* Variables and functions */
 int v4l2_prio_max (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cx18_g_priority(struct file *file, void *fh, enum v4l2_priority *p)
{
	struct cx18 *cx = ((struct cx18_open_id *)fh)->cx;

	*p = v4l2_prio_max(&cx->prio);
	return 0;
}