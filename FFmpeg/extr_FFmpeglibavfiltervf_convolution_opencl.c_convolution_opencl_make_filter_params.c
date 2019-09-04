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
typedef  scalar_t__ cl_mem ;
typedef  int cl_int ;
struct TYPE_8__ {TYPE_1__* hwctx; } ;
struct TYPE_9__ {double* biases; char** matrix_str; int* matrix_sizes; int* dims; scalar_t__* matrix; TYPE_2__ ocf; struct TYPE_9__* priv; } ;
struct TYPE_7__ {int /*<<< orphan*/  context; } ;
typedef  TYPE_3__ ConvolutionOpenCLContext ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int CL_MEM_COPY_HOST_PTR ; 
 int CL_MEM_HOST_NO_ACCESS ; 
 int CL_MEM_READ_ONLY ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_freep (float**) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 float* av_malloc (size_t) ; 
 char* av_strtok (char*,char*,char**) ; 
 scalar_t__ clCreateBuffer (int /*<<< orphan*/ ,int,size_t,float*,int*) ; 
 int sscanf (char*,char*,float*) ; 

__attribute__((used)) static int convolution_opencl_make_filter_params(AVFilterContext *avctx)
{
    ConvolutionOpenCLContext *ctx = avctx->priv;
    float *matrix = NULL;
    size_t matrix_bytes;
    cl_mem buffer;
    cl_int cle;
    int i, j;
    int sscanf_err;
    char *p, *arg, *saveptr = NULL;
    float input_matrix[4][49];

    for (i = 0; i < 4; i++) {
        ctx->biases[i] = ctx->biases[i] / 255.0;
    }

    for (i = 0; i < 4; i++) {
        p = ctx->matrix_str[i];
        while (ctx->matrix_sizes[i] < 49) {
            arg = av_strtok(p, " ", &saveptr);
            if (!arg) {
                break;
            }
            p = NULL;
            sscanf_err = sscanf(arg, "%f", &input_matrix[i][ctx->matrix_sizes[i]]);
            if (sscanf_err != 1) {
                av_log(ctx, AV_LOG_ERROR, "Matrix is sequence of 9, 25 or 49 signed numbers\n");
                return AVERROR(EINVAL);
            }
            ctx->matrix_sizes[i]++;
        }
        if (ctx->matrix_sizes[i] == 9) {
            ctx->dims[i] = 3;
        } else if (ctx->matrix_sizes[i] == 25) {
            ctx->dims[i] = 5;
        } else if (ctx->matrix_sizes[i] == 49) {
            ctx->dims[i] = 7;
        } else {
            av_log(ctx, AV_LOG_ERROR, "Invalid matrix size:%d\n", ctx->matrix_sizes[i]);
            return AVERROR(EINVAL);
        }

    }

    for (j = 0; j < 4; j++) {
        matrix_bytes = sizeof(float)*ctx->matrix_sizes[j];
        matrix = av_malloc(matrix_bytes);
        if (!matrix) {
            av_freep(&matrix);
            return AVERROR(ENOMEM);
        }

        for (i = 0; i < ctx->matrix_sizes[j]; i++)
            matrix[i] = input_matrix[j][i];

        buffer = clCreateBuffer(ctx->ocf.hwctx->context,
                                CL_MEM_READ_ONLY |
                                CL_MEM_COPY_HOST_PTR |
                                CL_MEM_HOST_NO_ACCESS,
                                matrix_bytes, matrix, &cle);
        if (!buffer) {
            av_log(avctx, AV_LOG_ERROR, "Failed to create matrix buffer: "
                   "%d.\n", cle);
            av_freep(&matrix);
            return AVERROR(EIO);
        }
        ctx->matrix[j] = buffer;
        av_freep(&matrix);
    }

    return 0;
}