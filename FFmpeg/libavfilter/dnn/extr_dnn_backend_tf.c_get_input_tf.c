#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_9__ {int height; int width; int channels; int /*<<< orphan*/  dt; } ;
struct TYPE_8__ {int /*<<< orphan*/  graph; } ;
struct TYPE_7__ {scalar_t__ index; int /*<<< orphan*/  oper; } ;
typedef  int /*<<< orphan*/  TF_Status ;
typedef  TYPE_1__ TF_Output ;
typedef  TYPE_2__ TFModel ;
typedef  int /*<<< orphan*/  DNNReturnType ;
typedef  TYPE_3__ DNNData ;

/* Variables and functions */
 int /*<<< orphan*/  DNN_ERROR ; 
 int /*<<< orphan*/  DNN_SUCCESS ; 
 int /*<<< orphan*/  TF_DeleteStatus (int /*<<< orphan*/ *) ; 
 scalar_t__ TF_GetCode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TF_GraphGetTensorShape (int /*<<< orphan*/ ,TYPE_1__,int*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TF_GraphOperationByName (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * TF_NewStatus () ; 
 scalar_t__ TF_OK ; 
 int /*<<< orphan*/  TF_OperationOutputType (TYPE_1__) ; 
 int /*<<< orphan*/  av_assert0 (int) ; 

__attribute__((used)) static DNNReturnType get_input_tf(void *model, DNNData *input, const char *input_name)
{
    TFModel *tf_model = (TFModel *)model;
    TF_Status *status;
    int64_t dims[4];

    TF_Output tf_output;
    tf_output.oper = TF_GraphOperationByName(tf_model->graph, input_name);
    if (!tf_output.oper)
        return DNN_ERROR;

    tf_output.index = 0;
    input->dt = TF_OperationOutputType(tf_output);

    status = TF_NewStatus();
    TF_GraphGetTensorShape(tf_model->graph, tf_output, dims, 4, status);
    if (TF_GetCode(status) != TF_OK){
        TF_DeleteStatus(status);
        return DNN_ERROR;
    }
    TF_DeleteStatus(status);

    // currently only NHWC is supported
    av_assert0(dims[0] == 1);
    input->height = dims[1];
    input->width = dims[2];
    input->channels = dims[3];

    return DNN_SUCCESS;
}