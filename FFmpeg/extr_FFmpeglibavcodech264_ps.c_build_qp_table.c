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
struct TYPE_3__ {int /*<<< orphan*/ ** chroma_qp_table; } ;
typedef  TYPE_1__ PPS ;

/* Variables and functions */
 size_t av_clip (int,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/ ** ff_h264_chroma_qp ; 

__attribute__((used)) static void build_qp_table(PPS *pps, int t, int index, const int depth)
{
    int i;
    const int max_qp = 51 + 6 * (depth - 8);
    for (i = 0; i < max_qp + 1; i++)
        pps->chroma_qp_table[t][i] =
            ff_h264_chroma_qp[depth - 8][av_clip(i + index, 0, max_qp)];
}