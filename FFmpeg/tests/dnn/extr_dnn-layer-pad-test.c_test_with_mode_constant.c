#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  expected_output ;
struct TYPE_6__ {float* data; int* dims; } ;
struct TYPE_5__ {int constant_values; int** paddings; int /*<<< orphan*/  mode; } ;
typedef  TYPE_1__ LayerPadParams ;
typedef  TYPE_2__ DnnOperand ;

/* Variables and functions */
 scalar_t__ EPSON ; 
 int /*<<< orphan*/  LPMP_CONSTANT ; 
 int /*<<< orphan*/  av_freep (float**) ; 
 int /*<<< orphan*/  dnn_execute_layer_pad (TYPE_2__*,scalar_t__*,int,TYPE_1__*) ; 
 scalar_t__ fabs (float) ; 
 int /*<<< orphan*/  printf (char*,int,float,float) ; 

__attribute__((used)) static int test_with_mode_constant(void)
{
    // the input data and expected data are generated with below python code.
    /*
    x = tf.placeholder(tf.float32, shape=[1, None, None, 3])
    y = tf.pad(x, [[0, 0], [1, 0], [0, 0], [1, 2]], 'CONSTANT', constant_values=728)
    data = np.arange(12).reshape(1, 2, 2, 3);

    sess=tf.Session()
    sess.run(tf.global_variables_initializer())
    output = sess.run(y, feed_dict={x: data})

    print(list(data.flatten()))
    print(list(output.flatten()))
    print(data.shape)
    print(output.shape)
    */

    LayerPadParams params;
    DnnOperand operands[2];
    int32_t input_indexes[1];
    float input[1*2*2*3] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
    };
    float expected_output[1*3*2*6] = {
        728.0, 728.0, 728.0, 728.0, 728.0, 728.0, 728.0, 728.0, 728.0, 728.0, 728.0,
        728.0, 728.0, 0.0, 1.0, 2.0, 728.0, 728.0, 728.0, 3.0, 4.0, 5.0, 728.0, 728.0,
        728.0, 6.0, 7.0, 8.0, 728.0, 728.0, 728.0, 9.0, 10.0, 11.0, 728.0, 728.0
    };
    float *output;

    params.mode = LPMP_CONSTANT;
    params.constant_values = 728;
    params.paddings[0][0] = 0;
    params.paddings[0][1] = 0;
    params.paddings[1][0] = 1;
    params.paddings[1][1] = 0;
    params.paddings[2][0] = 0;
    params.paddings[2][1] = 0;
    params.paddings[3][0] = 1;
    params.paddings[3][1] = 2;

    operands[0].data = input;
    operands[0].dims[0] = 1;
    operands[0].dims[1] = 2;
    operands[0].dims[2] = 2;
    operands[0].dims[3] = 3;
    operands[1].data = NULL;

    input_indexes[0] = 0;
    dnn_execute_layer_pad(operands, input_indexes, 1, &params);

    output = operands[1].data;
    for (int i = 0; i < sizeof(expected_output) / sizeof(float); i++) {
        if (fabs(output[i] - expected_output[i]) > EPSON) {
            printf("at index %d, output: %f, expected_output: %f\n", i, output[i], expected_output[i]);
            av_freep(&output);
            return 1;
        }
    }

    av_freep(&output);
    return 0;

}