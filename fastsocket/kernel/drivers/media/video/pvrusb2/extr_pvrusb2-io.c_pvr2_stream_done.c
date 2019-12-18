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
struct pvr2_stream {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pvr2_stream_buffer_count (struct pvr2_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvr2_stream_internal_flush (struct pvr2_stream*) ; 

__attribute__((used)) static void pvr2_stream_done(struct pvr2_stream *sp)
{
	mutex_lock(&sp->mutex); do {
		pvr2_stream_internal_flush(sp);
		pvr2_stream_buffer_count(sp,0);
	} while (0); mutex_unlock(&sp->mutex);
}