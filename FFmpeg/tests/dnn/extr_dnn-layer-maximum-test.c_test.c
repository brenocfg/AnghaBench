#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  input ;
struct TYPE_6__ {double y; } ;
struct TYPE_8__ {TYPE_1__ val; } ;
struct TYPE_7__ {float* data; int* dims; } ;
typedef  TYPE_2__ DnnOperand ;
typedef  TYPE_3__ DnnLayerMaximumParams ;

/* Variables and functions */
 scalar_t__ EPSON ; 
 int /*<<< orphan*/  av_freep (float**) ; 
 int /*<<< orphan*/  dnn_execute_layer_maximum (TYPE_2__*,scalar_t__*,int,TYPE_3__*) ; 
 scalar_t__ fabs (float) ; 
 int /*<<< orphan*/  printf (char*,int,float,float) ; 

__attribute__((used)) static int test(void)
{
    DnnLayerMaximumParams params;
    DnnOperand operands[2];
    int32_t input_indexes[1];
    float input[1*1*2*3] = {
        -3, 2.5, 2, -2.1, 7.8, 100
    };
    float *output;

    params.val.y = 2.3;

    operands[0].data = input;
    operands[0].dims[0] = 1;
    operands[0].dims[1] = 1;
    operands[0].dims[2] = 2;
    operands[0].dims[3] = 3;
    operands[1].data = NULL;

    input_indexes[0] = 0;
    dnn_execute_layer_maximum(operands, input_indexes, 1, &params);

    output = operands[1].data;
    for (int i = 0; i < sizeof(input) / sizeof(float); i++) {
        float expected_output = input[i] > params.val.y ? input[i] : params.val.y;
        if (fabs(output[i] - expected_output) > EPSON) {
            printf("at index %d, output: %f, expected_output: %f\n", i, output[i], expected_output);
            av_freep(&output);
            return 1;
        }
    }

    av_freep(&output);
    return 0;

}