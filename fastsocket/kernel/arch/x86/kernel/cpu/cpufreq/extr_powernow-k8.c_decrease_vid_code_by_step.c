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
typedef  scalar_t__ u32 ;
struct powernow_k8_data {scalar_t__ currvid; } ;

/* Variables and functions */
 int /*<<< orphan*/  count_off_vst (struct powernow_k8_data*) ; 
 scalar_t__ write_new_vid (struct powernow_k8_data*,scalar_t__) ; 

__attribute__((used)) static int decrease_vid_code_by_step(struct powernow_k8_data *data,
		u32 reqvid, u32 step)
{
	if ((data->currvid - reqvid) > step)
		reqvid = data->currvid - step;

	if (write_new_vid(data, reqvid))
		return 1;

	count_off_vst(data);

	return 0;
}