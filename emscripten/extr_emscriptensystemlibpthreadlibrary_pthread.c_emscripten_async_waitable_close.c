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
typedef  int /*<<< orphan*/  em_queued_call ;

/* Variables and functions */
 int /*<<< orphan*/  em_queued_call_free (int /*<<< orphan*/ *) ; 

void emscripten_async_waitable_close(em_queued_call *call)
{
	em_queued_call_free(call);
}