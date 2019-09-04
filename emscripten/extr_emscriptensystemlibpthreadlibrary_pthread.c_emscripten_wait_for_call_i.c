#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int i; } ;
struct TYPE_6__ {TYPE_1__ returnValue; } ;
typedef  TYPE_2__ em_queued_call ;
typedef  scalar_t__ EMSCRIPTEN_RESULT ;

/* Variables and functions */
 scalar_t__ EMSCRIPTEN_RESULT_SUCCESS ; 
 scalar_t__ emscripten_wait_for_call_v (TYPE_2__*,double) ; 

EMSCRIPTEN_RESULT emscripten_wait_for_call_i(em_queued_call *call, double timeoutMSecs, int *outResult)
{
	EMSCRIPTEN_RESULT res = emscripten_wait_for_call_v(call, timeoutMSecs);
	if (res == EMSCRIPTEN_RESULT_SUCCESS && outResult) *outResult = call->returnValue.i;
	return res;
}