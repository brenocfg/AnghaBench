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
struct ivtv_open_id {struct ivtv* itv; } ;
struct ivtv {int /*<<< orphan*/  std; } ;
struct file {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int ivtv_g_std(struct file *file, void *fh, v4l2_std_id *std)
{
	struct ivtv *itv = ((struct ivtv_open_id *)fh)->itv;

	*std = itv->std;
	return 0;
}