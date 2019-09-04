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
struct TYPE_5__ {TYPE_1__ desc; int /*<<< orphan*/  face; } ;
typedef  TYPE_2__ bbf_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  ccv_bbf_classifier_cascade_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 

void uri_bbf_detect_objects_destroy(void* context)
{
	bbf_context_t* bbf_context = (bbf_context_t*)context;
	ccv_bbf_classifier_cascade_free(bbf_context->face);
	free(bbf_context->desc.data);
	free(bbf_context);
}