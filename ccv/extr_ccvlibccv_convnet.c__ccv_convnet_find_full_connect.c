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
struct TYPE_5__ {int count; TYPE_1__* layers; } ;
typedef  TYPE_2__ ccv_convnet_t ;
struct TYPE_4__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ CCV_CONVNET_FULL_CONNECT ; 

__attribute__((used)) static int _ccv_convnet_find_full_connect(ccv_convnet_t* convnet)
{
	int i;
	for (i = 0; i < convnet->count; i++)
		if (convnet->layers[i].type == CCV_CONVNET_FULL_CONNECT)
			return i;
	return -1;
}