#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  network ;

/* Variables and functions */
 int gpu_index ; 
 int /*<<< orphan*/ * load_network (char*,char*,int) ; 
 int /*<<< orphan*/  save_weights_upto (int /*<<< orphan*/ *,char*,int) ; 

void partial(char *cfgfile, char *weightfile, char *outfile, int max)
{
    gpu_index = -1;
    network *net = load_network(cfgfile, weightfile, 1);
    save_weights_upto(net, outfile, max);
}