#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int count; TYPE_8__* layers; } ;
typedef  TYPE_7__ ccv_convnet_t ;
struct TYPE_15__ {int count; } ;
struct TYPE_14__ {int rows; int cols; int channels; } ;
struct TYPE_16__ {TYPE_5__ node; TYPE_4__ matrix; } ;
struct TYPE_12__ {int channels; int count; } ;
struct TYPE_11__ {scalar_t__ relu; } ;
struct TYPE_13__ {TYPE_2__ convolutional; TYPE_1__ full_connect; } ;
struct TYPE_18__ {scalar_t__ type; TYPE_6__ input; TYPE_3__ net; } ;
typedef  TYPE_8__ ccv_convnet_layer_t ;

/* Variables and functions */
 scalar_t__ CCV_CONVNET_CONVOLUTIONAL ; 
 scalar_t__ CCV_CONVNET_FULL_CONNECT ; 
 int /*<<< orphan*/  ccv_convnet_make_output (TYPE_8__*,int,int,int*,int*,int*) ; 

int ccv_convnet_verify(ccv_convnet_t* convnet, int output)
{
	int i, out_rows, out_cols, out_partition, out_channels;
	if (convnet->count < 1)
		return -1;
	// the last layer has to be full connect
	if (convnet->layers[convnet->count - 1].type != CCV_CONVNET_FULL_CONNECT)
		return -1;
	// you cannot enable relu on the last layer
	if (convnet->layers[convnet->count - 1].net.full_connect.relu)
		return -1;
	out_channels = 3;
	for (i = 0; i < convnet->count; i++)
	{
		ccv_convnet_layer_t* layer = convnet->layers + i;
		if (i > 0 && (out_rows != layer->input.matrix.rows || out_cols != layer->input.matrix.cols))
			return -1;
		// the input channels should be equal to the previous output channels, skip this check for full connect as it is meaningless
		if (out_channels != layer->input.matrix.channels && layer->type != CCV_CONVNET_FULL_CONNECT)
			return -1;
		ccv_convnet_make_output(layer, layer->input.matrix.rows, layer->input.matrix.cols, &out_rows, &out_cols, &out_partition);
		if (layer->type == CCV_CONVNET_CONVOLUTIONAL)
		{
			// check to see if the input matrix channel is equal to the expected input of the convolutional layer filters
			if (layer->input.matrix.channels != layer->net.convolutional.channels)
				return -1;
			// if this layer is convolutional layer, its filter output should equal to next layer's channel input
			out_channels = layer->net.convolutional.count;
		}
	}
	if (out_rows * out_cols != output)
		return -1;
	int count = 0;
	for (i = 0; i < convnet->count; i++)
	{
		ccv_convnet_layer_t* layer = convnet->layers + i;
		if (layer->type == CCV_CONVNET_FULL_CONNECT)
		{
			count = i;
			break;
		}
	}
	// all the layers after the first full connect layer should only be full connect layer
	for (i = count; i < convnet->count; i++)
		if (convnet->layers[i].type != CCV_CONVNET_FULL_CONNECT ||
			convnet->layers[i].input.matrix.rows * convnet->layers[i].input.matrix.cols * convnet->layers[i].input.matrix.channels != convnet->layers[i].input.node.count)
			return -1;
	return 0;
}