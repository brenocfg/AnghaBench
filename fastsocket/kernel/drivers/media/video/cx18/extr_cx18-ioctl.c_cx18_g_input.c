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
struct cx18 {unsigned int active_input; } ;

/* Variables and functions */

__attribute__((used)) static int cx18_g_input(struct file *file, void *fh, unsigned int *i)
{
	struct cx18 *cx = ((struct cx18_open_id *)fh)->cx;

	*i = cx->active_input;
	return 0;
}