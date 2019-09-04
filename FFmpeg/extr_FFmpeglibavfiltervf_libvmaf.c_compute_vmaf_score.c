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
struct TYPE_8__ {int /*<<< orphan*/  enable_conf_interval; int /*<<< orphan*/  n_subsample; int /*<<< orphan*/  n_threads; int /*<<< orphan*/  pool; int /*<<< orphan*/  ms_ssim; int /*<<< orphan*/  ssim; int /*<<< orphan*/  psnr; int /*<<< orphan*/  phone_model; int /*<<< orphan*/  enable_transform; int /*<<< orphan*/  log_fmt; int /*<<< orphan*/  log_path; int /*<<< orphan*/  model_path; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  vmaf_score; int /*<<< orphan*/  error; TYPE_2__* desc; } ;
struct TYPE_7__ {scalar_t__ name; TYPE_1__* comp; } ;
struct TYPE_6__ {int depth; } ;
typedef  TYPE_3__ LIBVMAFContext ;

/* Variables and functions */
 int /*<<< orphan*/  compute_vmaf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int (*) (float*,float*,float*,int,void*),TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int read_frame_10bit (float*,float*,float*,int,void*) ; 
 int read_frame_8bit (float*,float*,float*,int,void*) ; 

__attribute__((used)) static void compute_vmaf_score(LIBVMAFContext *s)
{
    int (*read_frame)(float *ref_data, float *main_data, float *temp_data,
                      int stride, void *ctx);
    char *format;

    if (s->desc->comp[0].depth <= 8) {
        read_frame = read_frame_8bit;
    } else {
        read_frame = read_frame_10bit;
    }

    format = (char *) s->desc->name;

    s->error = compute_vmaf(&s->vmaf_score, format, s->width, s->height,
                            read_frame, s, s->model_path, s->log_path,
                            s->log_fmt, 0, 0, s->enable_transform,
                            s->phone_model, s->psnr, s->ssim,
                            s->ms_ssim, s->pool,
                            s->n_threads, s->n_subsample, s->enable_conf_interval);
}