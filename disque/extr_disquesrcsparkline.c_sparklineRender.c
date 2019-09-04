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
struct sequence {int length; } ;
typedef  int /*<<< orphan*/  sds ;

/* Variables and functions */
 int /*<<< orphan*/  sdscatlen (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sparklineRenderRange (int /*<<< orphan*/ ,struct sequence*,int,int,int,int) ; 

sds sparklineRender(sds output, struct sequence *seq, int columns, int rows, int flags) {
    int j;

    for (j = 0; j < seq->length; j += columns) {
        int sublen = (seq->length-j) < columns ? (seq->length-j) : columns;

        if (j != 0) output = sdscatlen(output,"\n",1);
        output = sparklineRenderRange(output, seq, rows, j, sublen, flags);
    }
    return output;
}