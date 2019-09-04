#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int batch; int /*<<< orphan*/  truth; int /*<<< orphan*/  input; } ;
typedef  TYPE_1__ network ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  get_random_batch (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float train_network_datum (TYPE_1__*) ; 

float train_network_sgd(network *net, data d, int n)
{
    int batch = net->batch;

    int i;
    float sum = 0;
    for(i = 0; i < n; ++i){
        get_random_batch(d, batch, net->input, net->truth);
        float err = train_network_datum(net);
        sum += err;
    }
    return (float)sum/(n*batch);
}