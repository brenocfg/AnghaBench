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
struct TYPE_6__ {int /*<<< orphan*/  c; int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  inputs; int /*<<< orphan*/  batch; } ;
typedef  TYPE_1__ size_params ;
typedef  int /*<<< orphan*/  list ;
struct TYPE_7__ {int /*<<< orphan*/  out_c; int /*<<< orphan*/  out_h; int /*<<< orphan*/  out_w; } ;
typedef  TYPE_2__ dropout_layer ;

/* Variables and functions */
 TYPE_2__ make_dropout_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float) ; 
 float option_find_float (int /*<<< orphan*/ *,char*,double) ; 

dropout_layer parse_dropout(list *options, size_params params)
{
    float probability = option_find_float(options, "probability", .5);
    dropout_layer layer = make_dropout_layer(params.batch, params.inputs, probability);
    layer.out_w = params.w;
    layer.out_h = params.h;
    layer.out_c = params.c;
    return layer;
}