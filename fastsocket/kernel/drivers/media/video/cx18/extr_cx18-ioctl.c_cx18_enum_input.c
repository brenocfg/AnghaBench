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
struct v4l2_input {int /*<<< orphan*/  index; } ;
struct file {int dummy; } ;
struct cx18_open_id {struct cx18* cx; } ;
struct cx18 {int dummy; } ;

/* Variables and functions */
 int cx18_get_input (struct cx18*,int /*<<< orphan*/ ,struct v4l2_input*) ; 

__attribute__((used)) static int cx18_enum_input(struct file *file, void *fh, struct v4l2_input *vin)
{
	struct cx18 *cx = ((struct cx18_open_id *)fh)->cx;

	/* set it to defaults from our table */
	return cx18_get_input(cx, vin->index, vin);
}