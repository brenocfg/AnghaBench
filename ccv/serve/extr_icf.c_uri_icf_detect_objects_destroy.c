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
struct TYPE_5__ {TYPE_1__ desc; int /*<<< orphan*/  pedestrian; } ;
typedef  TYPE_2__ icf_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  ccv_icf_classifier_cascade_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 

void uri_icf_detect_objects_destroy(void* context)
{
	icf_context_t* icf_context = (icf_context_t*)context;
	ccv_icf_classifier_cascade_free(icf_context->pedestrian);
	free(icf_context->desc.data);
	free(icf_context);
}