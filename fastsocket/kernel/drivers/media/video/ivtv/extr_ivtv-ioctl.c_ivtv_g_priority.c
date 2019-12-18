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
struct ivtv_open_id {struct ivtv* itv; } ;
struct ivtv {int /*<<< orphan*/  prio; } ;
struct file {int dummy; } ;
typedef  enum v4l2_priority { ____Placeholder_v4l2_priority } v4l2_priority ;

/* Variables and functions */
 int v4l2_prio_max (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ivtv_g_priority(struct file *file, void *fh, enum v4l2_priority *p)
{
	struct ivtv *itv = ((struct ivtv_open_id *)fh)->itv;

	*p = v4l2_prio_max(&itv->prio);

	return 0;
}