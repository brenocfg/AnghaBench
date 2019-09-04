#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* data; } ;
struct TYPE_5__ {TYPE_1__ desc; int /*<<< orphan*/  semaphore; int /*<<< orphan*/  tlds; } ;
typedef  TYPE_2__ tld_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  ccv_array_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispatch_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 

void uri_tld_track_object_destroy(void* context)
{
	tld_context_t* tld_context = (tld_context_t*)context;
	ccv_array_free(tld_context->tlds);
	dispatch_release(tld_context->semaphore);
	free(tld_context->desc.data);
	free(tld_context);
}