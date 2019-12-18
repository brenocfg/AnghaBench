#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_6__ {int skip; TYPE_2__* out; TYPE_1__* in; } ;
typedef  TYPE_3__ ThreadData_convert_frame ;
struct TYPE_5__ {int*** grid; } ;
struct TYPE_4__ {int width; int height; int* linesize; scalar_t__** data; } ;
typedef  int /*<<< orphan*/  AVFilterContext ;

/* Variables and functions */
 int GRID_SIZE ; 
 int NUM_CELLS ; 
 int NUM_CHANNELS ; 

__attribute__((used)) static int convert_frame_partial(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    int cell, gx, gy, x0, x1, y0, y1, x, y, c, area;
    int sum[NUM_CHANNELS];
    const uint8_t *p;

    ThreadData_convert_frame *td = arg;

    const int slice_start = (NUM_CELLS * jobnr) / nb_jobs;
    const int slice_end = (NUM_CELLS * (jobnr+1)) / nb_jobs;

    int width = td->in->width, height = td->in->height, linesize = td->in->linesize[0], skip = td->skip;
    const uint8_t *data = td->in->data[0];

    for (cell = slice_start; cell < slice_end; cell++) {
        gx = cell % GRID_SIZE;
        gy = cell / GRID_SIZE;

        x0 = width  *  gx    / GRID_SIZE;
        x1 = width  * (gx+1) / GRID_SIZE;
        y0 = height *  gy    / GRID_SIZE;
        y1 = height * (gy+1) / GRID_SIZE;

        for (c = 0; c < NUM_CHANNELS; c++) {
            sum[c] = 0;
        }
        for (y = y0; y < y1; y += skip) {
            p = data + y * linesize + x0 * NUM_CHANNELS;
            for (x = x0; x < x1; x += skip) {
                //av_log(NULL, AV_LOG_VERBOSE, "%d %d %d : (%d,%d) (%d,%d) -> %d,%d | *%d\n", c, gx, gy, x0, y0, x1, y1, x, y, (int)row);
                sum[0] += p[0];
                sum[1] += p[1];
                sum[2] += p[2];
                p += NUM_CHANNELS * skip;
                // TODO: variable size
            }
        }

        area = ((x1 - x0 + skip - 1) / skip) * ((y1 - y0 + skip - 1) / skip);
        for (c = 0; c < NUM_CHANNELS; c++) {
            if (area)
                sum[c] /= area;
            td->out->grid[gy][gx][c] = sum[c];
        }
    }
    return 0;
}