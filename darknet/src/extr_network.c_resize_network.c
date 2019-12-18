#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int w; int h; int n; int inputs; int outputs; int truths; int batch; void* workspace; void* truth; void* truth_gpu; void* input; void* input_gpu; int /*<<< orphan*/  output; TYPE_2__* layers; int /*<<< orphan*/  gpu_index; } ;
typedef  TYPE_1__ network ;
struct TYPE_20__ {scalar_t__ type; size_t workspace_size; int outputs; int out_w; int out_h; int inputs; int truths; int /*<<< orphan*/  output; } ;
typedef  TYPE_2__ layer ;

/* Variables and functions */
 scalar_t__ AVGPOOL ; 
 scalar_t__ CONVOLUTIONAL ; 
 scalar_t__ COST ; 
 scalar_t__ CROP ; 
 scalar_t__ MAXPOOL ; 
 scalar_t__ NORMALIZATION ; 
 scalar_t__ REGION ; 
 scalar_t__ REORG ; 
 scalar_t__ ROUTE ; 
 scalar_t__ SHORTCUT ; 
 scalar_t__ UPSAMPLE ; 
 scalar_t__ YOLO ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 void* calloc (int,size_t) ; 
 int /*<<< orphan*/  cuda_free (void*) ; 
 void* cuda_make_array (void*,size_t) ; 
 int /*<<< orphan*/  cuda_set_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  free (void*) ; 
 TYPE_2__ get_network_output_layer (TYPE_1__*) ; 
 scalar_t__ gpu_index ; 
 int /*<<< orphan*/  resize_avgpool_layer (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  resize_convolutional_layer (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  resize_cost_layer (TYPE_2__*,int) ; 
 int /*<<< orphan*/  resize_crop_layer (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  resize_maxpool_layer (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  resize_normalization_layer (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  resize_region_layer (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  resize_reorg_layer (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  resize_route_layer (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  resize_shortcut_layer (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  resize_upsample_layer (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  resize_yolo_layer (TYPE_2__*,int,int) ; 

int resize_network(network *net, int w, int h)
{
#ifdef GPU
    cuda_set_device(net->gpu_index);
    cuda_free(net->workspace);
#endif
    int i;
    //if(w == net->w && h == net->h) return 0;
    net->w = w;
    net->h = h;
    int inputs = 0;
    size_t workspace_size = 0;
    //fprintf(stderr, "Resizing to %d x %d...\n", w, h);
    //fflush(stderr);
    for (i = 0; i < net->n; ++i){
        layer l = net->layers[i];
        if(l.type == CONVOLUTIONAL){
            resize_convolutional_layer(&l, w, h);
        }else if(l.type == CROP){
            resize_crop_layer(&l, w, h);
        }else if(l.type == MAXPOOL){
            resize_maxpool_layer(&l, w, h);
        }else if(l.type == REGION){
            resize_region_layer(&l, w, h);
        }else if(l.type == YOLO){
            resize_yolo_layer(&l, w, h);
        }else if(l.type == ROUTE){
            resize_route_layer(&l, net);
        }else if(l.type == SHORTCUT){
            resize_shortcut_layer(&l, w, h);
        }else if(l.type == UPSAMPLE){
            resize_upsample_layer(&l, w, h);
        }else if(l.type == REORG){
            resize_reorg_layer(&l, w, h);
        }else if(l.type == AVGPOOL){
            resize_avgpool_layer(&l, w, h);
        }else if(l.type == NORMALIZATION){
            resize_normalization_layer(&l, w, h);
        }else if(l.type == COST){
            resize_cost_layer(&l, inputs);
        }else{
            error("Cannot resize this type of layer");
        }
        if(l.workspace_size > workspace_size) workspace_size = l.workspace_size;
        if(l.workspace_size > 2000000000) assert(0);
        inputs = l.outputs;
        net->layers[i] = l;
        w = l.out_w;
        h = l.out_h;
        if(l.type == AVGPOOL) break;
    }
    layer out = get_network_output_layer(net);
    net->inputs = net->layers[0].inputs;
    net->outputs = out.outputs;
    net->truths = out.outputs;
    if(net->layers[net->n-1].truths) net->truths = net->layers[net->n-1].truths;
    net->output = out.output;
    free(net->input);
    free(net->truth);
    net->input = calloc(net->inputs*net->batch, sizeof(float));
    net->truth = calloc(net->truths*net->batch, sizeof(float));
#ifdef GPU
    if(gpu_index >= 0){
        cuda_free(net->input_gpu);
        cuda_free(net->truth_gpu);
        net->input_gpu = cuda_make_array(net->input, net->inputs*net->batch);
        net->truth_gpu = cuda_make_array(net->truth, net->truths*net->batch);
        if(workspace_size){
            net->workspace = cuda_make_array(0, (workspace_size-1)/sizeof(float)+1);
        }
    }else {
        free(net->workspace);
        net->workspace = calloc(1, workspace_size);
    }
#else
    free(net->workspace);
    net->workspace = calloc(1, workspace_size);
#endif
    //fprintf(stderr, " Done!\n");
    return 0;
}