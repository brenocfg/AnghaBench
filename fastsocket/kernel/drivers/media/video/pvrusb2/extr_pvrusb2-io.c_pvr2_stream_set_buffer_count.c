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
struct pvr2_stream {unsigned int buffer_target_count; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pvr2_stream_achieve_buffer_count (struct pvr2_stream*) ; 

int pvr2_stream_set_buffer_count(struct pvr2_stream *sp,unsigned int cnt)
{
	int ret;
	if (sp->buffer_target_count == cnt) return 0;
	mutex_lock(&sp->mutex); do {
		sp->buffer_target_count = cnt;
		ret = pvr2_stream_achieve_buffer_count(sp);
	} while(0); mutex_unlock(&sp->mutex);
	return ret;
}