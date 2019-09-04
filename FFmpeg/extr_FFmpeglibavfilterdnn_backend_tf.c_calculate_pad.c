#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_7__ {size_t layers_num; TYPE_1__* layers; } ;
struct TYPE_6__ {int kernel_size; } ;
struct TYPE_5__ {scalar_t__ type; scalar_t__ params; } ;
typedef  TYPE_2__ ConvolutionalParams ;
typedef  TYPE_3__ ConvolutionalNetwork ;

/* Variables and functions */
 scalar_t__ CONV ; 

__attribute__((used)) static int calculate_pad(const ConvolutionalNetwork *conv_network)
{
    ConvolutionalParams *params;
    int32_t layer;
    int pad = 0;

    for (layer = 0; layer < conv_network->layers_num; ++layer){
        if (conv_network->layers[layer].type == CONV){
            params = (ConvolutionalParams *)conv_network->layers[layer].params;
            pad += params->kernel_size >> 1;
        }
    }

    return pad;
}