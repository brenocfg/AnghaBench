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
struct cx18_stream {scalar_t__ handle; } ;
struct cx18 {struct cx18_stream* streams; } ;

/* Variables and functions */
 scalar_t__ CX18_INVALID_TASK_HANDLE ; 
 int CX18_MAX_STREAMS ; 
 scalar_t__ cx18_stream_enabled (struct cx18_stream*) ; 

struct cx18_stream *cx18_handle_to_stream(struct cx18 *cx, u32 handle)
{
	int i;
	struct cx18_stream *s;

	if (handle == CX18_INVALID_TASK_HANDLE)
		return NULL;

	for (i = 0; i < CX18_MAX_STREAMS; i++) {
		s = &cx->streams[i];
		if (s->handle != handle)
			continue;
		if (cx18_stream_enabled(s))
			return s;
	}
	return NULL;
}