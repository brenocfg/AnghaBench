#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
typedef  TYPE_1__ network ;
struct TYPE_10__ {int size; } ;
typedef  TYPE_2__ list ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 char** dice_labels ; 
 int /*<<< orphan*/  free_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_list (TYPE_2__*) ; 
 TYPE_2__* get_paths (char*) ; 
 scalar_t__ list_to_array (TYPE_2__*) ; 
 int /*<<< orphan*/  load_data_old (char**,int,int /*<<< orphan*/ ,char**,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_weights (TYPE_1__*,char*) ; 
 float* network_accuracies (TYPE_1__,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ parse_network_cfg (char*) ; 
 int /*<<< orphan*/  printf (char*,float,int) ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ ) ; 

void validate_dice(char *filename, char *weightfile)
{
    network net = parse_network_cfg(filename);
    if(weightfile){
        load_weights(&net, weightfile);
    }
    srand(time(0));

    char **labels = dice_labels;
    list *plist = get_paths("data/dice/dice.val.list");

    char **paths = (char **)list_to_array(plist);
    int m = plist->size;
    free_list(plist);

    data val = load_data_old(paths, m, 0, labels, 6, net.w, net.h);
    float *acc = network_accuracies(net, val, 2);
    printf("Validation Accuracy: %f, %d images\n", acc[0], m);
    free_data(val);
}