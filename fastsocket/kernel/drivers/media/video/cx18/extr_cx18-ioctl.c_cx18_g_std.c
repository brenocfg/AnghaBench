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
struct file {int dummy; } ;
struct cx18_open_id {struct cx18* cx; } ;
struct cx18 {int /*<<< orphan*/  std; } ;

/* Variables and functions */

__attribute__((used)) static int cx18_g_std(struct file *file, void *fh, v4l2_std_id *std)
{
	struct cx18 *cx = ((struct cx18_open_id *)fh)->cx;

	*std = cx->std;
	return 0;
}