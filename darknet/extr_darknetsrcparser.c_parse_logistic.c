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
struct TYPE_6__ {int /*<<< orphan*/  c; int /*<<< orphan*/  w; int /*<<< orphan*/  h; int /*<<< orphan*/  inputs; int /*<<< orphan*/  batch; } ;
typedef  TYPE_1__ size_params ;
typedef  int /*<<< orphan*/  list ;
struct TYPE_7__ {int /*<<< orphan*/  out_c; int /*<<< orphan*/  c; int /*<<< orphan*/  out_w; int /*<<< orphan*/  w; int /*<<< orphan*/  out_h; int /*<<< orphan*/  h; } ;
typedef  TYPE_2__ layer ;

/* Variables and functions */
 TYPE_2__ make_logistic_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

layer parse_logistic(list *options, size_params params)
{
    layer l = make_logistic_layer(params.batch, params.inputs);
    l.h = l.out_h = params.h;
    l.w = l.out_w = params.w;
    l.c = l.out_c = params.c;
    return l;
}