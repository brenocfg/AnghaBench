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
struct cx18_stream {int /*<<< orphan*/  out_work_order; struct cx18* cx; } ;
struct cx18 {int /*<<< orphan*/  out_work_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void cx18_stream_load_fw_queue(struct cx18_stream *s)
{
	struct cx18 *cx = s->cx;
	queue_work(cx->out_work_queue, &s->out_work_order);
}