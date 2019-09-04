#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  pthread_t ;
struct TYPE_14__ {double learning_rate; double momentum; double decay; int n; int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_4__* layers; } ;
typedef  TYPE_1__ network ;
struct TYPE_15__ {char* path; TYPE_5__* resized; TYPE_5__* im; int /*<<< orphan*/  type; int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ load_args ;
struct TYPE_16__ {int size; } ;
typedef  TYPE_3__ list ;
struct TYPE_17__ {int classes; int side; int n; } ;
typedef  TYPE_4__ layer ;
struct TYPE_18__ {float* data; int w; int h; } ;
typedef  TYPE_5__ image ;
typedef  int /*<<< orphan*/  detection ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  IMAGE_DATA ; 
 char* basecfg (char*) ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  do_nms_sort (int /*<<< orphan*/ *,int,int,float) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,double,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_detections (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free_image (TYPE_5__) ; 
 int /*<<< orphan*/ * get_network_boxes (TYPE_1__*,int,int,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 TYPE_3__* get_paths (char*) ; 
 scalar_t__ list_to_array (TYPE_3__*) ; 
 int /*<<< orphan*/  load_data_in_thread (TYPE_2__) ; 
 TYPE_1__* load_network (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  network_predict (TYPE_1__*,float*) ; 
 int /*<<< orphan*/  print_yolo_detections (int /*<<< orphan*/ **,char*,int,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_batch_network (TYPE_1__*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srand (scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * voc_names ; 

void validate_yolo(char *cfg, char *weights)
{
    network *net = load_network(cfg, weights, 0);
    set_batch_network(net, 1);
    fprintf(stderr, "Learning Rate: %g, Momentum: %g, Decay: %g\n", net->learning_rate, net->momentum, net->decay);
    srand(time(0));

    char *base = "results/comp4_det_test_";
    //list *plist = get_paths("data/voc.2007.test");
    list *plist = get_paths("/home/pjreddie/data/voc/2007_test.txt");
    //list *plist = get_paths("data/voc.2012.test");
    char **paths = (char **)list_to_array(plist);

    layer l = net->layers[net->n-1];
    int classes = l.classes;

    int j;
    FILE **fps = calloc(classes, sizeof(FILE *));
    for(j = 0; j < classes; ++j){
        char buff[1024];
        snprintf(buff, 1024, "%s%s.txt", base, voc_names[j]);
        fps[j] = fopen(buff, "w");
    }

    int m = plist->size;
    int i=0;
    int t;

    float thresh = .001;
    int nms = 1;
    float iou_thresh = .5;

    int nthreads = 8;
    image *val = calloc(nthreads, sizeof(image));
    image *val_resized = calloc(nthreads, sizeof(image));
    image *buf = calloc(nthreads, sizeof(image));
    image *buf_resized = calloc(nthreads, sizeof(image));
    pthread_t *thr = calloc(nthreads, sizeof(pthread_t));

    load_args args = {0};
    args.w = net->w;
    args.h = net->h;
    args.type = IMAGE_DATA;

    for(t = 0; t < nthreads; ++t){
        args.path = paths[i+t];
        args.im = &buf[t];
        args.resized = &buf_resized[t];
        thr[t] = load_data_in_thread(args);
    }
    time_t start = time(0);
    for(i = nthreads; i < m+nthreads; i += nthreads){
        fprintf(stderr, "%d\n", i);
        for(t = 0; t < nthreads && i+t-nthreads < m; ++t){
            pthread_join(thr[t], 0);
            val[t] = buf[t];
            val_resized[t] = buf_resized[t];
        }
        for(t = 0; t < nthreads && i+t < m; ++t){
            args.path = paths[i+t];
            args.im = &buf[t];
            args.resized = &buf_resized[t];
            thr[t] = load_data_in_thread(args);
        }
        for(t = 0; t < nthreads && i+t-nthreads < m; ++t){
            char *path = paths[i+t-nthreads];
            char *id = basecfg(path);
            float *X = val_resized[t].data;
            network_predict(net, X);
            int w = val[t].w;
            int h = val[t].h;
            int nboxes = 0;
            detection *dets = get_network_boxes(net, w, h, thresh, 0, 0, 0, &nboxes);
            if (nms) do_nms_sort(dets, l.side*l.side*l.n, classes, iou_thresh);
            print_yolo_detections(fps, id, l.side*l.side*l.n, classes, w, h, dets);
            free_detections(dets, nboxes);
            free(id);
            free_image(val[t]);
            free_image(val_resized[t]);
        }
    }
    fprintf(stderr, "Total Detection Time: %f Seconds\n", (double)(time(0) - start));
}