#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_5__* layers; } ;
typedef  TYPE_4__ ccv_convnet_t ;
struct TYPE_8__ {int strides; } ;
struct TYPE_7__ {int strides; } ;
struct TYPE_9__ {TYPE_2__ pool; TYPE_1__ convolutional; } ;
struct TYPE_11__ {int type; TYPE_3__ net; } ;
typedef  TYPE_5__ ccv_convnet_layer_t ;

/* Variables and functions */
#define  CCV_CONVNET_AVERAGE_POOL 130 
#define  CCV_CONVNET_CONVOLUTIONAL 129 
#define  CCV_CONVNET_MAX_POOL 128 

__attribute__((used)) static int _ccv_convnet_derive_scale(ccv_convnet_t* convnet, int scan)
{
	int i, scale = 1;
	for (i = scan; i >= 0; i--)
	{
		ccv_convnet_layer_t* layer = convnet->layers + i;
		switch (layer->type)
		{
			case CCV_CONVNET_CONVOLUTIONAL:
				scale *= layer->net.convolutional.strides;
				break;
			case CCV_CONVNET_MAX_POOL:
			case CCV_CONVNET_AVERAGE_POOL:
				scale *= layer->net.pool.strides;
				break;
		}
	}
	return scale;
}