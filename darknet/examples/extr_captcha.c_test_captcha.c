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
struct TYPE_10__ {float* data; } ;
typedef  TYPE_2__ image ;

/* Variables and functions */
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 char* fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_image (TYPE_2__) ; 
 char** get_labels (char*) ; 
 TYPE_2__ load_image_color (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* load_network (char*,char*,int /*<<< orphan*/ ) ; 
 float* network_predict (TYPE_1__*,float*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  set_batch_network (TYPE_1__*,int) ; 
 int /*<<< orphan*/  srand (int) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  strtok (char*,char*) ; 
 int /*<<< orphan*/  top_predictions (TYPE_1__*,int,int*) ; 

void test_captcha(char *cfgfile, char *weightfile, char *filename)
{
    network *net = load_network(cfgfile, weightfile, 0);
    set_batch_network(net, 1);
    srand(2222222);
    int i = 0;
    char **names = get_labels("/data/captcha/reimgs.labels.list");
    char buff[256];
    char *input = buff;
    int indexes[26];
    while(1){
        if(filename){
            strncpy(input, filename, 256);
        }else{
            //printf("Enter Image Path: ");
            //fflush(stdout);
            input = fgets(input, 256, stdin);
            if(!input) return;
            strtok(input, "\n");
        }
        image im = load_image_color(input, net->w, net->h);
        float *X = im.data;
        float *predictions = network_predict(net, X);
        top_predictions(net, 26, indexes);
        //printf("%s: Predicted in %f seconds.\n", input, sec(clock()-time));
        for(i = 0; i < 26; ++i){
            int index = indexes[i];
            if(i != 0) printf(", ");
            printf("%s %f", names[index], predictions[index]);
        }
        printf("\n");
        fflush(stdout);
        free_image(im);
        if (filename) break;
    }
}