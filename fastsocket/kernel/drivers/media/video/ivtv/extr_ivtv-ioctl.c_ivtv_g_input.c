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
struct ivtv {unsigned int active_input; } ;
struct file {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int ivtv_g_input(struct file *file, void *fh, unsigned int *i)
{
	struct ivtv *itv = ((struct ivtv_open_id *)fh)->itv;

	*i = itv->active_input;

	return 0;
}