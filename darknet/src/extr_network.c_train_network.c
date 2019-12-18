#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int batch; int /*<<< orphan*/  truth; int /*<<< orphan*/  input; } ;
typedef  TYPE_2__ network ;
struct TYPE_8__ {int rows; } ;
struct TYPE_10__ {TYPE_1__ X; } ;
typedef  TYPE_3__ data ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  get_next_batch (TYPE_3__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float train_network_datum (TYPE_2__*) ; 

float train_network(network *net, data d)
{
    assert(d.X.rows % net->batch == 0);
    int batch = net->batch;
    int n = d.X.rows / batch;

    int i;
    float sum = 0;
    for(i = 0; i < n; ++i){
        get_next_batch(d, batch, i*batch, net->input, net->truth);
        float err = train_network_datum(net);
        sum += err;
    }
    return (float)sum/(n*batch);
}