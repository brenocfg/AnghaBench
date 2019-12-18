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
struct cx18_stream {scalar_t__ handle; scalar_t__ video_dev; } ;
struct cx18 {struct cx18_stream* streams; } ;

/* Variables and functions */
 scalar_t__ CX18_INVALID_TASK_HANDLE ; 
 int CX18_MAX_STREAMS ; 

u32 cx18_find_handle(struct cx18 *cx)
{
	int i;

	/* find first available handle to be used for global settings */
	for (i = 0; i < CX18_MAX_STREAMS; i++) {
		struct cx18_stream *s = &cx->streams[i];

		if (s->video_dev && (s->handle != CX18_INVALID_TASK_HANDLE))
			return s->handle;
	}
	return CX18_INVALID_TASK_HANDLE;
}