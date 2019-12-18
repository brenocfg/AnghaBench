#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int partition; } ;
struct TYPE_14__ {TYPE_5__ matrix; } ;
struct TYPE_11__ {int border; int strides; int /*<<< orphan*/  size; } ;
struct TYPE_10__ {int count; } ;
struct TYPE_9__ {int rows; int cols; int border; int strides; } ;
struct TYPE_12__ {TYPE_3__ pool; TYPE_2__ full_connect; TYPE_1__ convolutional; } ;
struct TYPE_15__ {int type; TYPE_6__ input; TYPE_4__ net; } ;
typedef  TYPE_7__ ccv_convnet_layer_t ;

/* Variables and functions */
#define  CCV_CONVNET_AVERAGE_POOL 132 
#define  CCV_CONVNET_CONVOLUTIONAL 131 
#define  CCV_CONVNET_FULL_CONNECT 130 
#define  CCV_CONVNET_LOCAL_RESPONSE_NORM 129 
#define  CCV_CONVNET_MAX_POOL 128 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) inline static void ccv_convnet_make_output(ccv_convnet_layer_t* layer, int input_rows, int input_cols, int* rows, int* cols, int* partition)
{
	assert(rows != 0 && cols != 0);
	switch(layer->type)
	{
		case CCV_CONVNET_CONVOLUTIONAL:
			assert(layer->net.convolutional.rows % 2); // as of now, don't support even number of kernel size
			assert(layer->net.convolutional.cols % 2);
			assert((input_rows + layer->net.convolutional.border * 2 - layer->net.convolutional.rows) % layer->net.convolutional.strides == 0);
			assert((input_cols + layer->net.convolutional.border * 2 - layer->net.convolutional.cols) % layer->net.convolutional.strides == 0);
			*rows = (input_rows + layer->net.convolutional.border * 2 - layer->net.convolutional.rows + layer->net.convolutional.strides - 1) / layer->net.convolutional.strides + 1;
			*cols = (input_cols + layer->net.convolutional.border * 2 - layer->net.convolutional.cols + layer->net.convolutional.strides - 1) / layer->net.convolutional.strides + 1;
			*partition = layer->input.matrix.partition;
			break;
		case CCV_CONVNET_FULL_CONNECT:
			*rows = layer->net.full_connect.count;
			*cols = 1;
			*partition = 1;
			break;
		case CCV_CONVNET_LOCAL_RESPONSE_NORM:
			*rows = input_rows;
			*cols = input_cols;
			*partition = layer->input.matrix.partition;
			break;
		case CCV_CONVNET_MAX_POOL:
		case CCV_CONVNET_AVERAGE_POOL:
			assert((input_rows + layer->net.pool.border * 2 - layer->net.pool.size) % layer->net.pool.strides == 0);
			assert((input_cols + layer->net.pool.border * 2 - layer->net.pool.size) % layer->net.pool.strides == 0);
			*rows = (input_rows + layer->net.pool.border * 2 - layer->net.pool.size + layer->net.pool.strides - 1) / layer->net.pool.strides + 1;
			*cols = (input_cols + layer->net.pool.border * 2 - layer->net.pool.size + layer->net.pool.strides - 1) / layer->net.pool.strides + 1;
			*partition = layer->input.matrix.partition;
			break;
		default:
			assert(0);
			break;
	}
}