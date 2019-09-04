#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int batch; int inputs; int groups; int /*<<< orphan*/  loss; int /*<<< orphan*/ * cost; int /*<<< orphan*/  delta; scalar_t__ output; int /*<<< orphan*/  noloss; int /*<<< orphan*/  temperature; TYPE_1__* softmax_tree; } ;
typedef  TYPE_2__ softmax_layer ;
struct TYPE_8__ {scalar_t__ truth; scalar_t__ input; } ;
typedef  TYPE_3__ network ;
struct TYPE_6__ {int groups; int* group_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  softmax_cpu (scalar_t__,int,int,int,int,int,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  softmax_x_ent_cpu (int,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sum_array (int /*<<< orphan*/ ,int) ; 

void forward_softmax_layer(const softmax_layer l, network net)
{
    if(l.softmax_tree){
        int i;
        int count = 0;
        for (i = 0; i < l.softmax_tree->groups; ++i) {
            int group_size = l.softmax_tree->group_size[i];
            softmax_cpu(net.input + count, group_size, l.batch, l.inputs, 1, 0, 1, l.temperature, l.output + count);
            count += group_size;
        }
    } else {
        softmax_cpu(net.input, l.inputs/l.groups, l.batch, l.inputs, l.groups, l.inputs/l.groups, 1, l.temperature, l.output);
    }

    if(net.truth && !l.noloss){
        softmax_x_ent_cpu(l.batch*l.inputs, l.output, net.truth, l.delta, l.loss);
        l.cost[0] = sum_array(l.loss, l.batch*l.inputs);
    }
}