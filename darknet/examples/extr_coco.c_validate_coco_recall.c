#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {double learning_rate; double momentum; double decay; int n; int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_3__* layers; } ;
typedef  TYPE_1__ network ;
struct TYPE_24__ {int size; } ;
typedef  TYPE_2__ list ;
struct TYPE_25__ {int classes; int side; int n; } ;
typedef  TYPE_3__ layer ;
struct TYPE_26__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  data; } ;
typedef  TYPE_4__ image ;
struct TYPE_27__ {float objectness; int /*<<< orphan*/  bbox; } ;
typedef  TYPE_5__ detection ;
struct TYPE_28__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_6__ box_label ;
struct TYPE_29__ {int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_7__ box ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* basecfg (char*) ; 
 float box_iou (int /*<<< orphan*/ ,TYPE_7__) ; 
 int /*<<< orphan*/ ** calloc (int,int) ; 
 int /*<<< orphan*/ * coco_classes ; 
 int /*<<< orphan*/  do_nms_obj (TYPE_5__*,int,int,int) ; 
 int /*<<< orphan*/  find_replace (char*,char*,char*,char*) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_detections (TYPE_5__*,int) ; 
 int /*<<< orphan*/  free_image (TYPE_4__) ; 
 TYPE_5__* get_network_boxes (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 TYPE_2__* get_paths (char*) ; 
 scalar_t__ list_to_array (TYPE_2__*) ; 
 TYPE_4__ load_image_color (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* load_network (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  network_predict (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_6__* read_boxes (char*,int*) ; 
 TYPE_4__ resize_image (TYPE_4__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_batch_network (TYPE_1__*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ ) ; 

void validate_coco_recall(char *cfgfile, char *weightfile)
{
    network *net = load_network(cfgfile, weightfile, 0);
    set_batch_network(net, 1);
    fprintf(stderr, "Learning Rate: %g, Momentum: %g, Decay: %g\n", net->learning_rate, net->momentum, net->decay);
    srand(time(0));

    char *base = "results/comp4_det_test_";
    list *plist = get_paths("/home/pjreddie/data/voc/test/2007_test.txt");
    char **paths = (char **)list_to_array(plist);

    layer l = net->layers[net->n-1];
    int classes = l.classes;
    int side = l.side;

    int j, k;
    FILE **fps = calloc(classes, sizeof(FILE *));
    for(j = 0; j < classes; ++j){
        char buff[1024];
        snprintf(buff, 1024, "%s%s.txt", base, coco_classes[j]);
        fps[j] = fopen(buff, "w");
    }

    int m = plist->size;
    int i=0;

    float thresh = .001;
    int nms = 0;
    float iou_thresh = .5;

    int total = 0;
    int correct = 0;
    int proposals = 0;
    float avg_iou = 0;

    for(i = 0; i < m; ++i){
        char *path = paths[i];
        image orig = load_image_color(path, 0, 0);
        image sized = resize_image(orig, net->w, net->h);
        char *id = basecfg(path);
        network_predict(net, sized.data);

        int nboxes = 0;
        detection *dets = get_network_boxes(net, orig.w, orig.h, thresh, 0, 0, 1, &nboxes);
        if (nms) do_nms_obj(dets, side*side*l.n, 1, nms);

        char labelpath[4096];
        find_replace(path, "images", "labels", labelpath);
        find_replace(labelpath, "JPEGImages", "labels", labelpath);
        find_replace(labelpath, ".jpg", ".txt", labelpath);
        find_replace(labelpath, ".JPEG", ".txt", labelpath);

        int num_labels = 0;
        box_label *truth = read_boxes(labelpath, &num_labels);
        for(k = 0; k < side*side*l.n; ++k){
            if(dets[k].objectness > thresh){
                ++proposals;
            }
        }
        for (j = 0; j < num_labels; ++j) {
            ++total;
            box t = {truth[j].x, truth[j].y, truth[j].w, truth[j].h};
            float best_iou = 0;
            for(k = 0; k < side*side*l.n; ++k){
                float iou = box_iou(dets[k].bbox, t);
                if(dets[k].objectness > thresh && iou > best_iou){
                    best_iou = iou;
                }
            }
            avg_iou += best_iou;
            if(best_iou > iou_thresh){
                ++correct;
            }
        }
        free_detections(dets, nboxes);
        fprintf(stderr, "%5d %5d %5d\tRPs/Img: %.2f\tIOU: %.2f%%\tRecall:%.2f%%\n", i, correct, total, (float)proposals/(i+1), avg_iou*100/total, 100.*correct/total);
        free(id);
        free_image(orig);
        free_image(sized);
    }
}