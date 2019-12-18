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
struct rgbvec {float r; float g; float b; } ;
typedef  int /*<<< orphan*/  line ;
struct TYPE_9__ {TYPE_2__* priv; } ;
struct TYPE_7__ {void* b; void* g; void* r; } ;
struct TYPE_8__ {TYPE_1__ scale; struct rgbvec* lut; } ;
typedef  TYPE_2__ LUT3DContext ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int MAX_LINE_SIZE ; 
 int /*<<< orphan*/  NEXT_LINE (int /*<<< orphan*/ ) ; 
 int allocate_3dlut (TYPE_3__*,int const) ; 
 void* av_clipf (int,float,float) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,float,float,float,float,float,float) ; 
 int av_sscanf (char*,char*,float*,float*,float*) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ skip_line (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int strtol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_cube(AVFilterContext *ctx, FILE *f)
{
    LUT3DContext *lut3d = ctx->priv;
    char line[MAX_LINE_SIZE];
    float min[3] = {0.0, 0.0, 0.0};
    float max[3] = {1.0, 1.0, 1.0};

    while (fgets(line, sizeof(line), f)) {
        if (!strncmp(line, "LUT_3D_SIZE", 11)) {
            int ret, i, j, k;
            const int size = strtol(line + 12, NULL, 0);
            const int size2 = size * size;

            ret = allocate_3dlut(ctx, size);
            if (ret < 0)
                return ret;

            for (k = 0; k < size; k++) {
                for (j = 0; j < size; j++) {
                    for (i = 0; i < size; i++) {
                        struct rgbvec *vec = &lut3d->lut[i * size2 + j * size + k];

                        do {
try_again:
                            NEXT_LINE(0);
                            if (!strncmp(line, "DOMAIN_", 7)) {
                                float *vals = NULL;
                                if      (!strncmp(line + 7, "MIN ", 4)) vals = min;
                                else if (!strncmp(line + 7, "MAX ", 4)) vals = max;
                                if (!vals)
                                    return AVERROR_INVALIDDATA;
                                av_sscanf(line + 11, "%f %f %f", vals, vals + 1, vals + 2);
                                av_log(ctx, AV_LOG_DEBUG, "min: %f %f %f | max: %f %f %f\n",
                                       min[0], min[1], min[2], max[0], max[1], max[2]);
                                goto try_again;
                            } else if (!strncmp(line, "TITLE", 5)) {
                                goto try_again;
                            }
                        } while (skip_line(line));
                        if (av_sscanf(line, "%f %f %f", &vec->r, &vec->g, &vec->b) != 3)
                            return AVERROR_INVALIDDATA;
                    }
                }
            }
            break;
        }
    }

    lut3d->scale.r = av_clipf(1. / (max[0] - min[0]), 0.f, 1.f);
    lut3d->scale.g = av_clipf(1. / (max[1] - min[1]), 0.f, 1.f);
    lut3d->scale.b = av_clipf(1. / (max[2] - min[2]), 0.f, 1.f);

    return 0;
}