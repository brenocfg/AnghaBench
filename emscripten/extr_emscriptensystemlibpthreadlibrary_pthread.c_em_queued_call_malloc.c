#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ js; scalar_t__ satelliteData; scalar_t__ functionPtr; scalar_t__ operationDone; } ;
typedef  TYPE_1__ em_queued_call ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ malloc (int) ; 

__attribute__((used)) static em_queued_call *em_queued_call_malloc()
{
	em_queued_call *call = (em_queued_call*)malloc(sizeof(em_queued_call));
	assert(call); // Not a programming error, but use assert() in debug builds to catch OOM scenarios.
	if (call)
	{
		call->operationDone = 0;
		call->functionPtr = 0;
		call->satelliteData = 0;
		call->js = 0;
	}
	return call;
}