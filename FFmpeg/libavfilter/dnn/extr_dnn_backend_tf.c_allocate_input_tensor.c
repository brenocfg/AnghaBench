#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_3__ {int height; int width; int channels; int dt; } ;
typedef  int /*<<< orphan*/  TF_Tensor ;
typedef  int /*<<< orphan*/  TF_DataType ;
typedef  TYPE_1__ DNNData ;

/* Variables and functions */
#define  DNN_FLOAT 129 
#define  DNN_UINT8 128 
 int /*<<< orphan*/ * TF_AllocateTensor (int /*<<< orphan*/ ,int*,int,int) ; 
 int /*<<< orphan*/  TF_FLOAT ; 
 int /*<<< orphan*/  TF_UINT8 ; 
 int /*<<< orphan*/  av_assert0 (int) ; 

__attribute__((used)) static TF_Tensor *allocate_input_tensor(const DNNData *input)
{
    TF_DataType dt;
    size_t size;
    int64_t input_dims[] = {1, input->height, input->width, input->channels};
    switch (input->dt) {
    case DNN_FLOAT:
        dt = TF_FLOAT;
        size = sizeof(float);
        break;
    case DNN_UINT8:
        dt = TF_UINT8;
        size = sizeof(char);
        break;
    default:
        av_assert0(!"should not reach here");
    }

    return TF_AllocateTensor(dt, input_dims, 4,
                             input_dims[1] * input_dims[2] * input_dims[3] * size);
}