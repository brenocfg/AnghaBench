#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  linesize; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  frame_block_to_cell (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void create_clusters(const AVFrame *frame, int w, int h, uint8_t *yuvClusters)
{
    int i, j, k, l;

    for (i=0; i<h; i+=4)
        for (j=0; j<w; j+=4) {
            for (k=0; k < 2; k++)
                for (l=0; l < 2; l++)
                    frame_block_to_cell(yuvClusters + (l + 2*k)*6, frame->data,
                                        i+2*k, j+2*l, frame->linesize);
            yuvClusters += 24;
        }
}