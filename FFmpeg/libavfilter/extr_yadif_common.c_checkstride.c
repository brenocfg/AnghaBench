#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* csp; } ;
typedef  TYPE_2__ YADIFContext ;
struct TYPE_9__ {scalar_t__* linesize; } ;
struct TYPE_7__ {int nb_components; } ;
typedef  TYPE_3__ AVFrame ;

/* Variables and functions */

__attribute__((used)) static int checkstride(YADIFContext *yadif, const AVFrame *a, const AVFrame *b)
{
    int i;
    for (i = 0; i < yadif->csp->nb_components; i++)
        if (a->linesize[i] != b->linesize[i])
            return 1;
    return 0;
}