#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  outputs; int /*<<< orphan*/  output; } ;
typedef  TYPE_1__ network ;

/* Variables and functions */
 int /*<<< orphan*/  top_k (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 

void top_predictions(network *net, int k, int *index)
{
    top_k(net->output, net->outputs, k, index);
}