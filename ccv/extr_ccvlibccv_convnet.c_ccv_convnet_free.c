#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int count; scalar_t__ mean_activity; TYPE_1__* layers; } ;
typedef  TYPE_2__ ccv_convnet_t ;
struct TYPE_6__ {TYPE_2__* w; } ;

/* Variables and functions */
 int /*<<< orphan*/  ccfree (TYPE_2__*) ; 
 int /*<<< orphan*/  ccv_convnet_compact (TYPE_2__*) ; 
 int /*<<< orphan*/  ccv_matrix_free (scalar_t__) ; 

void ccv_convnet_free(ccv_convnet_t* convnet)
{
	ccv_convnet_compact(convnet);
	int i;
	for (i = 0; i < convnet->count; i++)
		if (convnet->layers[i].w)
			ccfree(convnet->layers[i].w);
	if (convnet->mean_activity)
		ccv_matrix_free(convnet->mean_activity);
	ccfree(convnet);
}