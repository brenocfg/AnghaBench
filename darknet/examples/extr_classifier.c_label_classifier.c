#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int w; int h; } ;
typedef  TYPE_1__ network ;
struct TYPE_20__ {int size; } ;
typedef  TYPE_2__ list ;
struct TYPE_21__ {int w; int h; scalar_t__ data; } ;
typedef  TYPE_3__ image ;

/* Variables and functions */
 TYPE_3__ crop_image (TYPE_3__,int,int,int,int) ; 
 int /*<<< orphan*/  free_image (TYPE_3__) ; 
 int /*<<< orphan*/  free_list (TYPE_2__*) ; 
 char** get_labels (char*) ; 
 TYPE_2__* get_paths (char*) ; 
 scalar_t__ list_to_array (TYPE_2__*) ; 
 TYPE_3__ load_image_color (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* load_network (char*,char*,int /*<<< orphan*/ ) ; 
 int max_index (float*,int) ; 
 float* network_predict (TYPE_1__*,scalar_t__) ; 
 int option_find_int (TYPE_2__*,char*,int) ; 
 char* option_find_str (TYPE_2__*,char*,char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 TYPE_2__* read_data_cfg (char*) ; 
 TYPE_3__ resize_min (TYPE_3__,int) ; 
 int /*<<< orphan*/  set_batch_network (TYPE_1__*,int) ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ ) ; 

void label_classifier(char *datacfg, char *filename, char *weightfile)
{
    int i;
    network *net = load_network(filename, weightfile, 0);
    set_batch_network(net, 1);
    srand(time(0));

    list *options = read_data_cfg(datacfg);

    char *label_list = option_find_str(options, "names", "data/labels.list");
    char *test_list = option_find_str(options, "test", "data/train.list");
    int classes = option_find_int(options, "classes", 2);

    char **labels = get_labels(label_list);
    list *plist = get_paths(test_list);

    char **paths = (char **)list_to_array(plist);
    int m = plist->size;
    free_list(plist);

    for(i = 0; i < m; ++i){
        image im = load_image_color(paths[i], 0, 0);
        image resized = resize_min(im, net->w);
        image crop = crop_image(resized, (resized.w - net->w)/2, (resized.h - net->h)/2, net->w, net->h);
        float *pred = network_predict(net, crop.data);

        if(resized.data != im.data) free_image(resized);
        free_image(im);
        free_image(crop);
        int ind = max_index(pred, classes);

        printf("%s\n", labels[ind]);
    }
}