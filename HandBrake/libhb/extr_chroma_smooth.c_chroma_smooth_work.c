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
typedef  int /*<<< orphan*/  hb_filter_object_t ;
typedef  int /*<<< orphan*/  hb_buffer_t ;

/* Variables and functions */
 int chroma_smooth_work_thread (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int chroma_smooth_work(hb_filter_object_t *filter,
                              hb_buffer_t ** buf_in,
                              hb_buffer_t ** buf_out)
{
    return chroma_smooth_work_thread(filter, buf_in, buf_out, 0);
}