#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_7__ ;
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pthread_t ;
struct TYPE_32__ {int n; double learning_rate; double momentum; double decay; int batch; int subdivisions; int* seen; int inputs; int train; scalar_t__ max_batches; float* input_gpu; float* truth_gpu; int truths; float* delta_gpu; float* cost; int /*<<< orphan*/  c; int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_6__* layers; scalar_t__ delta; } ;
typedef  TYPE_3__ network ;
struct TYPE_33__ {char** paths; int n; int classes; char** labels; int /*<<< orphan*/  type; TYPE_7__* d; int /*<<< orphan*/  m; } ;
typedef  TYPE_4__ load_args ;
struct TYPE_34__ {int /*<<< orphan*/  size; } ;
typedef  TYPE_5__ list ;
struct TYPE_35__ {int out_c; int outputs; int batch; float* delta_gpu; scalar_t__ output; int /*<<< orphan*/  output_gpu; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_6__ layer ;
typedef  int /*<<< orphan*/  image ;
struct TYPE_31__ {int /*<<< orphan*/ * vals; } ;
struct TYPE_30__ {double** vals; } ;
struct TYPE_36__ {TYPE_2__ X; TYPE_1__ y; } ;
typedef  TYPE_7__ data ;
typedef  scalar_t__ clock_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLASSIFICATION_DATA ; 
 int /*<<< orphan*/  axpy_gpu (int,int,float*,int,float*,int) ; 
 int /*<<< orphan*/  backward_network_gpu (TYPE_3__*) ; 
 char* basecfg (char*) ; 
 float* calloc (int,int) ; 
 scalar_t__ clock () ; 
 TYPE_7__ concat_data (TYPE_7__,TYPE_7__) ; 
 int /*<<< orphan*/  copy_cpu (int,scalar_t__,int,int /*<<< orphan*/ ,int) ; 
 TYPE_7__ copy_data (TYPE_7__) ; 
 int /*<<< orphan*/  copy_gpu (int,int /*<<< orphan*/ ,int,float*,int) ; 
 double cuda_mag_array (float*,int) ; 
 float* cuda_make_array (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cuda_push_array (float*,float*,int) ; 
 int /*<<< orphan*/  fill_gpu (int,double,float*,int) ; 
 int /*<<< orphan*/  float_to_image (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  forward_network_gpu (TYPE_3__*) ; 
 int /*<<< orphan*/  free_data (TYPE_7__) ; 
 TYPE_4__ get_base_args (TYPE_3__*) ; 
 scalar_t__ get_current_batch (TYPE_3__*) ; 
 double get_current_rate (TYPE_3__*) ; 
 int /*<<< orphan*/  get_next_batch (TYPE_7__,int,int,float*,int /*<<< orphan*/ ) ; 
 TYPE_5__* get_paths (char*) ; 
 int /*<<< orphan*/  grayscale_image_3c (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  harmless_update_network_gpu (TYPE_3__*) ; 
 scalar_t__ list_to_array (TYPE_5__*) ; 
 int /*<<< orphan*/  load_data_in_thread (TYPE_4__) ; 
 TYPE_3__* load_network (char*,char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save_weights (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  scal_gpu (int,int,float*,int) ; 
 int /*<<< orphan*/  sec (scalar_t__) ; 
 int /*<<< orphan*/  show_image (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*,...) ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 
 scalar_t__ time ; 
 float train_network (TYPE_3__*,TYPE_7__) ; 
 int /*<<< orphan*/  update_network_gpu (TYPE_3__*) ; 

void train_colorizer(char *cfg, char *weight, char *acfg, char *aweight, int clear, int display)
{
#ifdef GPU
    //char *train_images = "/home/pjreddie/data/coco/train1.txt";
    //char *train_images = "/home/pjreddie/data/coco/trainvalno5k.txt";
    char *train_images = "/home/pjreddie/data/imagenet/imagenet1k.train.list";
    char *backup_directory = "/home/pjreddie/backup/";
    srand(time(0));
    char *base = basecfg(cfg);
    char *abase = basecfg(acfg);
    printf("%s\n", base);
    network *net = load_network(cfg, weight, clear);
    network *anet = load_network(acfg, aweight, clear);

    int i, j, k;
    layer imlayer = {0};
    for (i = 0; i < net->n; ++i) {
        if (net->layers[i].out_c == 3) {
            imlayer = net->layers[i];
            break;
        }
    }

    printf("Learning Rate: %g, Momentum: %g, Decay: %g\n", net->learning_rate, net->momentum, net->decay);
    int imgs = net->batch*net->subdivisions;
    i = *net->seen/imgs;
    data train, buffer;


    list *plist = get_paths(train_images);
    //int N = plist->size;
    char **paths = (char **)list_to_array(plist);

    load_args args= get_base_args(net);
    args.paths = paths;
    args.n = imgs;
    args.m = plist->size;
    args.d = &buffer;

    args.type = CLASSIFICATION_DATA;
    args.classes = 1;
    char *ls[2] = {"imagenet"};
    args.labels = ls;

    pthread_t load_thread = load_data_in_thread(args);
    clock_t time;

    int x_size = net->inputs*net->batch;
    //int y_size = x_size;
    net->delta = 0;
    net->train = 1;
    float *pixs = calloc(x_size, sizeof(float));
    float *graypixs = calloc(x_size, sizeof(float));
    //float *y = calloc(y_size, sizeof(float));

    //int ay_size = anet->outputs*anet->batch;
    anet->delta = 0;
    anet->train = 1;

    float *imerror = cuda_make_array(0, imlayer.outputs*imlayer.batch);

    float aloss_avg = -1;
    float gloss_avg = -1;

    //data generated = copy_data(train);

    while (get_current_batch(net) < net->max_batches) {
        i += 1;
        time=clock();
        pthread_join(load_thread, 0);
        train = buffer;
        load_thread = load_data_in_thread(args);

        printf("Loaded: %lf seconds\n", sec(clock()-time));

        data gray = copy_data(train);
        for(j = 0; j < imgs; ++j){
            image gim = float_to_image(net->w, net->h, net->c, gray.X.vals[j]);
            grayscale_image_3c(gim);
            train.y.vals[j][0] = .95;
            gray.y.vals[j][0] = .05;
        }
        time=clock();
        float gloss = 0;

        for(j = 0; j < net->subdivisions; ++j){
            get_next_batch(train, net->batch, j*net->batch, pixs, 0);
            get_next_batch(gray, net->batch, j*net->batch, graypixs, 0);
            cuda_push_array(net->input_gpu, graypixs, net->inputs*net->batch);
            cuda_push_array(net->truth_gpu, pixs, net->truths*net->batch);
            /*
               image origi = float_to_image(net->w, net->h, 3, pixs);
               image grayi = float_to_image(net->w, net->h, 3, graypixs);
               show_image(grayi, "gray");
               show_image(origi, "orig");
               cvWaitKey(0);
             */
            *net->seen += net->batch;
            forward_network_gpu(net);

            fill_gpu(imlayer.outputs*imlayer.batch, 0, imerror, 1);
            copy_gpu(anet->inputs*anet->batch, imlayer.output_gpu, 1, anet->input_gpu, 1);
            fill_gpu(anet->inputs*anet->batch, .95, anet->truth_gpu, 1);
            anet->delta_gpu = imerror;
            forward_network_gpu(anet);
            backward_network_gpu(anet);

            scal_gpu(imlayer.outputs*imlayer.batch, 1./100., net->layers[net->n-1].delta_gpu, 1);

            scal_gpu(imlayer.outputs*imlayer.batch, 1, imerror, 1);

            printf("realness %f\n", cuda_mag_array(imerror, imlayer.outputs*imlayer.batch));
            printf("features %f\n", cuda_mag_array(net->layers[net->n-1].delta_gpu, imlayer.outputs*imlayer.batch));

            axpy_gpu(imlayer.outputs*imlayer.batch, 1, imerror, 1, net->layers[net->n-1].delta_gpu, 1);

            backward_network_gpu(net);


            gloss += *net->cost /(net->subdivisions*net->batch);

            for(k = 0; k < net->batch; ++k){
                int index = j*net->batch + k;
                copy_cpu(imlayer.outputs, imlayer.output + k*imlayer.outputs, 1, gray.X.vals[index], 1);
            }
        }
        harmless_update_network_gpu(anet);

        data merge = concat_data(train, gray);
        //randomize_data(merge);
        float aloss = train_network(anet, merge);

        update_network_gpu(net);

#ifdef OPENCV
        if(display){
            image im = float_to_image(anet->w, anet->h, anet->c, gray.X.vals[0]);
            image im2 = float_to_image(anet->w, anet->h, anet->c, train.X.vals[0]);
            show_image(im, "gen", 1);
            show_image(im2, "train", 1);
        }
#endif
        free_data(merge);
        free_data(train);
        free_data(gray);
        if (aloss_avg < 0) aloss_avg = aloss;
        aloss_avg = aloss_avg*.9 + aloss*.1;
        gloss_avg = gloss_avg*.9 + gloss*.1;

        printf("%d: gen: %f, adv: %f | gen_avg: %f, adv_avg: %f, %f rate, %lf seconds, %d images\n", i, gloss, aloss, gloss_avg, aloss_avg, get_current_rate(net), sec(clock()-time), i*imgs);
        if(i%1000==0){
            char buff[256];
            sprintf(buff, "%s/%s_%d.weights", backup_directory, base, i);
            save_weights(net, buff);
            sprintf(buff, "%s/%s_%d.weights", backup_directory, abase, i);
            save_weights(anet, buff);
        }
        if(i%100==0){
            char buff[256];
            sprintf(buff, "%s/%s.backup", backup_directory, base);
            save_weights(net, buff);
            sprintf(buff, "%s/%s.backup", backup_directory, abase);
            save_weights(anet, buff);
        }
    }
    char buff[256];
    sprintf(buff, "%s/%s_final.weights", backup_directory, base);
    save_weights(net, buff);
#endif
}