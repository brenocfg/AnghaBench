#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  outputs; int /*<<< orphan*/  hierarchy; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
typedef  TYPE_1__ network ;
struct TYPE_17__ {int size; } ;
typedef  TYPE_2__ list ;
struct TYPE_18__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ image ;

/* Variables and functions */
 int* calloc (int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,double,int,int) ; 
 int /*<<< orphan*/  free_image (TYPE_3__) ; 
 int /*<<< orphan*/  free_list (TYPE_2__*) ; 
 TYPE_2__* get_paths (char*) ; 
 int /*<<< orphan*/  hierarchy_predictions (float*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 TYPE_3__ letterbox_image (TYPE_3__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ list_to_array (TYPE_2__*) ; 
 TYPE_3__ load_image_color (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* load_network (char*,char*,int /*<<< orphan*/ ) ; 
 float* network_predict (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int option_find_int (TYPE_2__*,char*,int) ; 
 char* option_find_str (TYPE_2__*,char*,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_2__* read_data_cfg (char*) ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  top_k (float*,int /*<<< orphan*/ ,int,int*) ; 
 double what_time_is_it_now () ; 

void csv_classifier(char *datacfg, char *cfgfile, char *weightfile)
{
    int i,j;
    network *net = load_network(cfgfile, weightfile, 0);
    srand(time(0));

    list *options = read_data_cfg(datacfg);

    char *test_list = option_find_str(options, "test", "data/test.list");
    int top = option_find_int(options, "top", 1);

    list *plist = get_paths(test_list);

    char **paths = (char **)list_to_array(plist);
    int m = plist->size;
    free_list(plist);
    int *indexes = calloc(top, sizeof(int));

    for(i = 0; i < m; ++i){
        double time = what_time_is_it_now();
        char *path = paths[i];
        image im = load_image_color(path, 0, 0);
        image r = letterbox_image(im, net->w, net->h);
        float *predictions = network_predict(net, r.data);
        if(net->hierarchy) hierarchy_predictions(predictions, net->outputs, net->hierarchy, 1, 1);
        top_k(predictions, net->outputs, top, indexes);

        printf("%s", path);
        for(j = 0; j < top; ++j){
            printf("\t%d", indexes[j]);
        }
        printf("\n");

        free_image(im);
        free_image(r);

        fprintf(stderr, "%lf seconds, %d images, %d total\n", what_time_is_it_now() - time, i+1, m);
    }
}