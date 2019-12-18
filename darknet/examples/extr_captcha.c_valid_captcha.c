#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int outputs; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
typedef  TYPE_1__ network ;
struct TYPE_12__ {int size; } ;
typedef  TYPE_2__ list ;
struct TYPE_13__ {float* data; } ;
typedef  TYPE_3__ image ;

/* Variables and functions */
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free_image (TYPE_3__) ; 
 char** get_labels (char*) ; 
 TYPE_2__* get_paths (char*) ; 
 scalar_t__ list_to_array (TYPE_2__*) ; 
 TYPE_3__ load_image_color (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* load_network (char*,char*,int /*<<< orphan*/ ) ; 
 float* network_predict (TYPE_1__*,float*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  set_batch_network (TYPE_1__*,int) ; 
 int /*<<< orphan*/  srand (int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strstr (char*,char*) ; 

void valid_captcha(char *cfgfile, char *weightfile, char *filename)
{
    char **labels = get_labels("/data/captcha/reimgs.labels.list");
    network *net = load_network(cfgfile, weightfile, 0);
    list *plist = get_paths("/data/captcha/reimgs.fg.list");
    char **paths = (char **)list_to_array(plist);
    int N = plist->size;
    int outputs = net->outputs;

    set_batch_network(net, 1);
    srand(2222222);
    int i, j;
    for(i = 0; i < N; ++i){
        if (i%100 == 0) fprintf(stderr, "%d\n", i);
        image im = load_image_color(paths[i], net->w, net->h);
        float *X = im.data;
        float *predictions = network_predict(net, X);
        //printf("%s: Predicted in %f seconds.\n", input, sec(clock()-time));
        int truth = -1;
        for(j = 0; j < 13; ++j){
            if (strstr(paths[i], labels[j])) truth = j;
        }
        if (truth == -1){
            fprintf(stderr, "bad: %s\n", paths[i]);
            return;
        }
        printf("%d, ", truth);
        for(j = 0; j < outputs; ++j){
            if (j != 0) printf(", ");
            printf("%f", predictions[j]);
        }
        printf("\n");
        fflush(stdout);
        free_image(im);
        if (filename) break;
    }
}