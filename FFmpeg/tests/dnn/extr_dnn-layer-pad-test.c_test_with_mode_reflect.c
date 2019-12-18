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
struct TYPE_5__ {int** paddings; int /*<<< orphan*/  mode; } ;
typedef  TYPE_1__ LayerPadParams ;
typedef  TYPE_2__ DnnOperand ;

/* Variables and functions */
 scalar_t__ EPSON ; 
 int /*<<< orphan*/  LPMP_REFLECT ; 
 int /*<<< orphan*/  av_freep (float**) ; 
 int /*<<< orphan*/  dnn_execute_layer_pad (TYPE_2__*,scalar_t__*,int,TYPE_1__*) ; 
 scalar_t__ fabs (float) ; 
 int /*<<< orphan*/  printf (char*,int,float,float) ; 

__attribute__((used)) static int test_with_mode_reflect(void)
{
    // the input data and expected data are generated with below python code.
    /*
    x = tf.placeholder(tf.float32, shape=[3, None, None, 3])
    y = tf.pad(x, [[1, 2], [0, 0], [0, 0], [0, 0]], 'REFLECT')
    data = np.arange(36).reshape(3, 2, 2, 3);

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
    float input[3*2*2*3] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35
    };
    float expected_output[6*2*2*3] = {
        12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0,
        12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0, 29.0, 30.0, 31.0, 32.0, 33.0, 34.0,
        35.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0
    };
    float *output;

    params.mode = LPMP_REFLECT;
    params.paddings[0][0] = 1;
    params.paddings[0][1] = 2;
    params.paddings[1][0] = 0;
    params.paddings[1][1] = 0;
    params.paddings[2][0] = 0;
    params.paddings[2][1] = 0;
    params.paddings[3][0] = 0;
    params.paddings[3][1] = 0;

    operands[0].data = input;
    operands[0].dims[0] = 3;
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