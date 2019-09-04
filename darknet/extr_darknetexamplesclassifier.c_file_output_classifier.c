#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int w; int h; int /*<<< orphan*/  hierarchy; int /*<<< orphan*/  outputs; } ;
typedef  TYPE_1__ network ;
struct TYPE_19__ {int size; } ;
typedef  TYPE_2__ list ;
struct TYPE_20__ {int w; int h; scalar_t__ data; } ;
typedef  TYPE_3__ image ;

/* Variables and functions */
 TYPE_3__ crop_image (TYPE_3__,int,int,int,int) ; 
 int /*<<< orphan*/  free_image (TYPE_3__) ; 
 int /*<<< orphan*/  free_list (TYPE_2__*) ; 
 TYPE_2__* get_paths (char*) ; 
 int /*<<< orphan*/  hierarchy_predictions (float*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ list_to_array (TYPE_2__*) ; 
 TYPE_3__ load_image_color (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* load_network (char*,char*,int /*<<< orphan*/ ) ; 
 float* network_predict (TYPE_1__*,scalar_t__) ; 
 int option_find_int (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_2__* read_data_cfg (char*) ; 
 TYPE_3__ resize_min (TYPE_3__,int) ; 
 int /*<<< orphan*/  set_batch_network (TYPE_1__*,int) ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ ) ; 

void file_output_classifier(char *datacfg, char *filename, char *weightfile, char *listfile)
{
    int i,j;
    network *net = load_network(filename, weightfile, 0);
    set_batch_network(net, 1);
    srand(time(0));

    list *options = read_data_cfg(datacfg);

    //char *label_list = option_find_str(options, "names", "data/labels.list");
    int classes = option_find_int(options, "classes", 2);

    list *plist = get_paths(listfile);

    char **paths = (char **)list_to_array(plist);
    int m = plist->size;
    free_list(plist);

    for(i = 0; i < m; ++i){
        image im = load_image_color(paths[i], 0, 0);
        image resized = resize_min(im, net->w);
        image crop = crop_image(resized, (resized.w - net->w)/2, (resized.h - net->h)/2, net->w, net->h);

        float *pred = network_predict(net, crop.data);
        if(net->hierarchy) hierarchy_predictions(pred, net->outputs, net->hierarchy, 0, 1);

        if(resized.data != im.data) free_image(resized);
        free_image(im);
        free_image(crop);

        printf("%s", paths[i]);
        for(j = 0; j < classes; ++j){
            printf("\t%g", pred[j]);
        }
        printf("\n");
    }
}