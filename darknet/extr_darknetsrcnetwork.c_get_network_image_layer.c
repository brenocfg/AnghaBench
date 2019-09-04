#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* layers; } ;
typedef  TYPE_1__ network ;
struct TYPE_8__ {int /*<<< orphan*/  output; scalar_t__ out_c; scalar_t__ out_h; scalar_t__ out_w; } ;
typedef  TYPE_2__ layer ;
struct TYPE_9__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ image ;

/* Variables and functions */
 TYPE_3__ float_to_image (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

image get_network_image_layer(network *net, int i)
{
    layer l = net->layers[i];
#ifdef GPU
    //cuda_pull_array(l.output_gpu, l.output, l.outputs);
#endif
    if (l.out_w && l.out_h && l.out_c){
        return float_to_image(l.out_w, l.out_h, l.out_c, l.output);
    }
    image def = {0};
    return def;
}