#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* output_data; scalar_t__ input_tensor; scalar_t__ status; scalar_t__ session; scalar_t__ graph; scalar_t__ model; } ;
struct TYPE_6__ {TYPE_2__* data; } ;
typedef  TYPE_2__ TFModel ;
typedef  TYPE_2__ DNNModel ;

/* Variables and functions */
 int /*<<< orphan*/  TF_CloseSession (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TF_DeleteGraph (scalar_t__) ; 
 int /*<<< orphan*/  TF_DeleteSession (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TF_DeleteStatus (scalar_t__) ; 
 int /*<<< orphan*/  TF_DeleteTensor (scalar_t__) ; 
 int /*<<< orphan*/  av_freep (TYPE_2__**) ; 

void ff_dnn_free_model_tf(DNNModel **model)
{
    TFModel *tf_model;

    if (*model){
        tf_model = (TFModel *)(*model)->model;
        if (tf_model->graph){
            TF_DeleteGraph(tf_model->graph);
        }
        if (tf_model->session){
            TF_CloseSession(tf_model->session, tf_model->status);
            TF_DeleteSession(tf_model->session, tf_model->status);
        }
        if (tf_model->status){
            TF_DeleteStatus(tf_model->status);
        }
        if (tf_model->input_tensor){
            TF_DeleteTensor(tf_model->input_tensor);
        }
        if (tf_model->output_data){
            av_freep(&tf_model->output_data->data);
        }
        av_freep(&tf_model);
        av_freep(model);
    }
}