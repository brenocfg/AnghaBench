#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  AVBPrint ;

/* Variables and functions */
 int /*<<< orphan*/  av_bprintf (int /*<<< orphan*/ *,char*,...) ; 

void ff_opencl_print_const_matrix_3x3(AVBPrint *buf, const char *name_str,
                                      double mat[3][3])
{
    int i, j;
    av_bprintf(buf, "__constant float %s[9] = {\n", name_str);
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++)
            av_bprintf(buf, " %.5ff,", mat[i][j]);
        av_bprintf(buf, "\n");
    }
    av_bprintf(buf, "};\n");
}