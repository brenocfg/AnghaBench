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
struct rgbvec {int /*<<< orphan*/  b; int /*<<< orphan*/  g; int /*<<< orphan*/  r; } ;
struct TYPE_6__ {TYPE_1__* priv; } ;
struct TYPE_5__ {int lutsize; struct rgbvec* lut; } ;
typedef  TYPE_1__ LUT3DContext ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int MAX_LINE_SIZE ; 
 int /*<<< orphan*/  NEXT_LINE (int /*<<< orphan*/ ) ; 
 int allocate_3dlut (TYPE_2__*,int) ; 
 int av_sscanf (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_line (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int strtol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_dat(AVFilterContext *ctx, FILE *f)
{
    LUT3DContext *lut3d = ctx->priv;
    char line[MAX_LINE_SIZE];
    int ret, i, j, k, size, size2;

    lut3d->lutsize = size = 33;
    size2 = size * size;

    NEXT_LINE(skip_line(line));
    if (!strncmp(line, "3DLUTSIZE ", 10)) {
        size = strtol(line + 10, NULL, 0);

        NEXT_LINE(skip_line(line));
    }

    ret = allocate_3dlut(ctx, size);
    if (ret < 0)
        return ret;

    for (k = 0; k < size; k++) {
        for (j = 0; j < size; j++) {
            for (i = 0; i < size; i++) {
                struct rgbvec *vec = &lut3d->lut[k * size2 + j * size + i];
                if (k != 0 || j != 0 || i != 0)
                    NEXT_LINE(skip_line(line));
                if (av_sscanf(line, "%f %f %f", &vec->r, &vec->g, &vec->b) != 3)
                    return AVERROR_INVALIDDATA;
            }
        }
    }
    return 0;
}