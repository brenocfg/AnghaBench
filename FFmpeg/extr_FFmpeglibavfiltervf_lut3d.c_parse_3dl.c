#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rgbvec {int r; int g; int b; } ;
struct TYPE_5__ {TYPE_1__* priv; } ;
struct TYPE_4__ {int lutsize; struct rgbvec*** lut; } ;
typedef  TYPE_1__ LUT3DContext ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int MAX_LINE_SIZE ; 
 int /*<<< orphan*/  NEXT_LINE (int /*<<< orphan*/ ) ; 
 int av_sscanf (char*,char*,int*,int*,int*) ; 
 int /*<<< orphan*/  skip_line (char*) ; 

__attribute__((used)) static int parse_3dl(AVFilterContext *ctx, FILE *f)
{
    char line[MAX_LINE_SIZE];
    LUT3DContext *lut3d = ctx->priv;
    int i, j, k;
    const int size = 17;
    const float scale = 16*16*16;

    lut3d->lutsize = size;
    NEXT_LINE(skip_line(line));
    for (k = 0; k < size; k++) {
        for (j = 0; j < size; j++) {
            for (i = 0; i < size; i++) {
                int r, g, b;
                struct rgbvec *vec = &lut3d->lut[k][j][i];

                NEXT_LINE(skip_line(line));
                if (av_sscanf(line, "%d %d %d", &r, &g, &b) != 3)
                    return AVERROR_INVALIDDATA;
                vec->r = r / scale;
                vec->g = g / scale;
                vec->b = b / scale;
            }
        }
    }
    return 0;
}