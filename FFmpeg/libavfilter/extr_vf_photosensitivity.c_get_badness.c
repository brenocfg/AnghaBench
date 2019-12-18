#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__*** grid; } ;
typedef  TYPE_1__ PhotosensitivityFrame ;

/* Variables and functions */
 int GRID_SIZE ; 
 int NUM_CHANNELS ; 
 scalar_t__ abs (int) ; 

__attribute__((used)) static int get_badness(PhotosensitivityFrame *a, PhotosensitivityFrame *b)
{
    int badness, x, y, c;
    badness = 0;
    for (c = 0; c < NUM_CHANNELS; c++) {
        for (y = 0; y < GRID_SIZE; y++) {
            for (x = 0; x < GRID_SIZE; x++) {
                badness += abs((int)a->grid[y][x][c] - (int)b->grid[y][x][c]);
                //av_log(NULL, AV_LOG_VERBOSE, "%d - %d -> %d \n", a->grid[y][x], b->grid[y][x], badness);
                //av_log(NULL, AV_LOG_VERBOSE, "%d -> %d \n", abs((int)a->grid[y][x] - (int)b->grid[y][x]), badness);
            }
        }
    }
    return badness;
}