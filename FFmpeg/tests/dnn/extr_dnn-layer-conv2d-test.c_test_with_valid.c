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
struct TYPE_6__ {int has_bias; float* biases; int dilation; int input_num; float* kernel; int kernel_size; int output_num; int /*<<< orphan*/  padding_method; int /*<<< orphan*/  activation; } ;
struct TYPE_5__ {float* data; int* dims; } ;
typedef  TYPE_1__ DnnOperand ;
typedef  TYPE_2__ ConvolutionalParams ;

/* Variables and functions */
 scalar_t__ EPSON ; 
 int /*<<< orphan*/  TANH ; 
 int /*<<< orphan*/  VALID ; 
 int /*<<< orphan*/  av_freep (float**) ; 
 int /*<<< orphan*/  dnn_execute_layer_conv2d (TYPE_1__*,scalar_t__*,int,TYPE_2__*) ; 
 scalar_t__ fabs (float) ; 
 int /*<<< orphan*/  printf (char*,int,float,float) ; 

__attribute__((used)) static int test_with_valid(void)
{
    // the input data and expected data are generated with below python code.
    /*
    x = tf.placeholder(tf.float32, shape=[1, None, None, 3])
    y = tf.layers.conv2d(x, 2, 3, activation=tf.nn.tanh, padding='valid', bias_initializer=tf.keras.initializers.he_normal())
    data = np.random.rand(1, 5, 6, 3);

    sess=tf.Session()
    sess.run(tf.global_variables_initializer())

    weights = dict([(var.name, sess.run(var)) for var in tf.trainable_variables()])
    kernel = weights['conv2d/kernel:0']
    kernel = np.transpose(kernel, [3, 0, 1, 2])
    print("kernel:")
    print(kernel.shape)
    print(list(kernel.flatten()))

    bias = weights['conv2d/bias:0']
    print("bias:")
    print(bias.shape)
    print(list(bias.flatten()))

    output = sess.run(y, feed_dict={x: data})

    print("input:")
    print(data.shape)
    print(list(data.flatten()))

    print("output:")
    print(output.shape)
    print(list(output.flatten()))
    */

    ConvolutionalParams params;
    DnnOperand operands[2];
    int32_t input_indexes[1];
    float input[1*5*6*3] = {
        0.26126657468269665, 0.42762216215337556, 0.7466274030131497, 0.802550266787863, 0.3709323443076644, 0.5919817068197668, 0.49274512279324967,
        0.7170132295090351, 0.0911793215410649, 0.5134213878288361, 0.670132600785118, 0.49417034512633484, 0.03887389460089885, 0.436785102836845,
        0.1490231658611978, 0.6413606121498127, 0.8595987991375995, 0.9132593077586231, 0.7075959004873255, 0.17754995944845464, 0.5212507214937141,
        0.35379732738215475, 0.25205107358505296, 0.3928792840544273, 0.09485294189485782, 0.8685115437448666, 0.6489046799288605, 0.509253797582924,
        0.8993255536791972, 0.18740056466602373, 0.34237617336313986, 0.3871438962989183, 0.1488532571774911, 0.5187002331293636, 0.8137098818752955,
        0.521761863717401, 0.4622312310118274, 0.29038411334638825, 0.16194915718170566, 0.5175999923925211, 0.8852230040101133, 0.0218263385047206,
        0.08482355352852367, 0.3463638568376264, 0.28627127120619733, 0.9553293378948409, 0.4803391055970835, 0.841635695030805, 0.3556828280031952,
        0.06778527221541808, 0.28193560357091596, 0.8399957619031576, 0.03305536359456385, 0.6625039162109645, 0.9300552020023897, 0.8551529138204146,
        0.6133216915522418, 0.222427800857393, 0.1315422686800336, 0.6189144989185527, 0.5346184916866876, 0.8348888624532548, 0.6544834567840291,
        0.2844062293389934, 0.28780026600883324, 0.5372272015684924, 0.6250226011503823, 0.28119106062279453, 0.49655812908420094, 0.6451488959145951,
        0.7362580606834843, 0.44815578616664087, 0.6454760235835586, 0.6794062414265861, 0.045378883014935756, 0.9008388543865096, 0.7949752851269782,
        0.4179928876222264, 0.28733419007048644, 0.996902319501908, 0.5690851338677467, 0.9511814013279738, 0.025323788678181636, 0.5594359732604794,
        0.1213732595086251, 0.7172624313368294, 0.6759328959074691, 0.07252138454885071, 0.17557735158403442, 0.5988895455048769
    };
    float expected_output[1*3*4*2] = {
        -0.556947, -0.42143887, -0.092070885, 0.27404794, -0.41886684, 0.0862887, -0.25001016, -0.342721, 0.020730592, 0.04016919, -0.69839877,
        -0.06136704, 0.14186388, -0.11655602, -0.23489095, -0.3845829, -0.19017771, 0.1595885, -0.18308741, -0.3071209, -0.5848686, -0.22509028,
        -0.6023201, -0.14448485
    };
    float *output;
    float kernel[2*3*3*3] = {
        -0.25291282, 0.22402048, 0.028642118, -0.14615723, -0.27362752, -0.34801802, -0.2759148, 0.19594926, -0.25029412, 0.34606284, 0.10376671,
        -0.1015394, 0.23616093, 0.2134214, 0.35285157, 0.05893758, 0.0024731457, -0.17143056, 0.35758412, 0.2186206, -0.28384736, -0.21206513,
        -0.20871592, 0.27070445, 0.25878823, 0.11136332, -0.33737376, 0.08353335, -0.34290665, 0.041805506, -0.09738535, 0.3284936, -0.16838405,
        -0.032494456, -0.29193437, 0.033259362, -0.09272635, -0.2802651, -0.28648436, 0.3542878, 0.2432127, -0.24551713, 0.27813476, 0.21024024,
        -0.013690501, -0.1350077, -0.07826337, -0.34563828, 0.3220685, -0.07571727, 0.19420576, 0.20783454, 0.18738335, 0.16672492
    };
    float bias[2] = { -0.4773722, -0.19620377 };

    params.activation = TANH;
    params.has_bias = 1;
    params.biases = bias;
    params.dilation = 1;
    params.input_num = 3;
    params.kernel = kernel;
    params.kernel_size = 3;
    params.output_num = 2;
    params.padding_method = VALID;

    operands[0].data = input;
    operands[0].dims[0] = 1;
    operands[0].dims[1] = 5;
    operands[0].dims[2] = 6;
    operands[0].dims[3] = 3;
    operands[1].data = NULL;

    input_indexes[0] = 0;
    dnn_execute_layer_conv2d(operands, input_indexes, 1, &params);

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