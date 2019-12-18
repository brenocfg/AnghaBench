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
struct ql3_adapter {scalar_t__ small_buf_index; int /*<<< orphan*/  small_buf_release_cnt; } ;

/* Variables and functions */
 scalar_t__ NUM_SMALL_BUFFERS ; 

__attribute__((used)) static void ql_get_sbuf(struct ql3_adapter *qdev)
{
	if (++qdev->small_buf_index == NUM_SMALL_BUFFERS)
		qdev->small_buf_index = 0;
	qdev->small_buf_release_cnt++;
}