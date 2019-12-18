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
typedef  int uint8_t ;
struct rgbvec {float r; float g; float b; } ;
typedef  int /*<<< orphan*/  line ;
struct TYPE_7__ {TYPE_1__* priv; } ;
struct TYPE_6__ {int lutsize; struct rgbvec* lut; } ;
typedef  TYPE_1__ LUT3DContext ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int MAX_LEVEL ; 
 int MAX_LINE_SIZE ; 
 int /*<<< orphan*/  NEXT_LINE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_COLOR (int) ; 
 int allocate_3dlut (TYPE_2__*,int) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,...) ; 
 int av_sscanf (char*,char*,float*,float*,float*) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int strtol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_m3d(AVFilterContext *ctx, FILE *f)
{
    LUT3DContext *lut3d = ctx->priv;
    float scale;
    int ret, i, j, k, size, size2, in = -1, out = -1;
    char line[MAX_LINE_SIZE];
    uint8_t rgb_map[3] = {0, 1, 2};

    while (fgets(line, sizeof(line), f)) {
        if      (!strncmp(line, "in",  2)) in  = strtol(line + 2, NULL, 0);
        else if (!strncmp(line, "out", 3)) out = strtol(line + 3, NULL, 0);
        else if (!strncmp(line, "values", 6)) {
            const char *p = line + 6;
#define SET_COLOR(id) do {                  \
    while (av_isspace(*p))                  \
        p++;                                \
    switch (*p) {                           \
    case 'r': rgb_map[id] = 0; break;       \
    case 'g': rgb_map[id] = 1; break;       \
    case 'b': rgb_map[id] = 2; break;       \
    }                                       \
    while (*p && !av_isspace(*p))           \
        p++;                                \
} while (0)
            SET_COLOR(0);
            SET_COLOR(1);
            SET_COLOR(2);
            break;
        }
    }

    if (in == -1 || out == -1) {
        av_log(ctx, AV_LOG_ERROR, "in and out must be defined\n");
        return AVERROR_INVALIDDATA;
    }
    if (in < 2 || out < 2 ||
        in  > MAX_LEVEL*MAX_LEVEL*MAX_LEVEL ||
        out > MAX_LEVEL*MAX_LEVEL*MAX_LEVEL) {
        av_log(ctx, AV_LOG_ERROR, "invalid in (%d) or out (%d)\n", in, out);
        return AVERROR_INVALIDDATA;
    }
    for (size = 1; size*size*size < in; size++);
    lut3d->lutsize = size;
    size2 = size * size;

    ret = allocate_3dlut(ctx, size);
    if (ret < 0)
        return ret;

    scale = 1. / (out - 1);

    for (k = 0; k < size; k++) {
        for (j = 0; j < size; j++) {
            for (i = 0; i < size; i++) {
                struct rgbvec *vec = &lut3d->lut[k * size2 + j * size + i];
                float val[3];

                NEXT_LINE(0);
                if (av_sscanf(line, "%f %f %f", val, val + 1, val + 2) != 3)
                    return AVERROR_INVALIDDATA;
                vec->r = val[rgb_map[0]] * scale;
                vec->g = val[rgb_map[1]] * scale;
                vec->b = val[rgb_map[2]] * scale;
            }
        }
    }
    return 0;
}