#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * set_input_output; void* model; int /*<<< orphan*/ * output_data; int /*<<< orphan*/ * input_tensor; int /*<<< orphan*/ * session; } ;
typedef  TYPE_1__ TFModel ;
typedef  TYPE_1__ DNNModel ;

/* Variables and functions */
 scalar_t__ DNN_SUCCESS ; 
 int /*<<< orphan*/  av_freep (TYPE_1__**) ; 
 TYPE_1__* av_malloc (int) ; 
 scalar_t__ load_native_model (TYPE_1__*,char const*) ; 
 scalar_t__ load_tf_model (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  set_input_output_tf ; 

DNNModel *ff_dnn_load_model_tf(const char *model_filename)
{
    DNNModel *model = NULL;
    TFModel *tf_model = NULL;

    model = av_malloc(sizeof(DNNModel));
    if (!model){
        return NULL;
    }

    tf_model = av_malloc(sizeof(TFModel));
    if (!tf_model){
        av_freep(&model);
        return NULL;
    }
    tf_model->session = NULL;
    tf_model->input_tensor = NULL;
    tf_model->output_data = NULL;

    if (load_tf_model(tf_model, model_filename) != DNN_SUCCESS){
        if (load_native_model(tf_model, model_filename) != DNN_SUCCESS){
            av_freep(&tf_model);
            av_freep(&model);

            return NULL;
        }
    }

    model->model = (void *)tf_model;
    model->set_input_output = &set_input_output_tf;

    return model;
}