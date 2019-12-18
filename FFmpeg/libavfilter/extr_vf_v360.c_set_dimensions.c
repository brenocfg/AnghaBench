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
struct TYPE_3__ {int /*<<< orphan*/  log2_chroma_h; int /*<<< orphan*/  log2_chroma_w; } ;
typedef  TYPE_1__ AVPixFmtDescriptor ;

/* Variables and functions */
 int FF_CEIL_RSHIFT (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_dimensions(int *outw, int *outh, int w, int h, const AVPixFmtDescriptor *desc)
{
    outw[1] = outw[2] = FF_CEIL_RSHIFT(w, desc->log2_chroma_w);
    outw[0] = outw[3] = w;
    outh[1] = outh[2] = FF_CEIL_RSHIFT(h, desc->log2_chroma_h);
    outh[0] = outh[3] = h;
}