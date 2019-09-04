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
struct TYPE_6__ {scalar_t__ num_ch; } ;
struct TYPE_5__ {TYPE_2__* group; } ;
typedef  TYPE_1__ FFPsyContext ;
typedef  TYPE_2__ FFPsyChannelGroup ;

/* Variables and functions */

FFPsyChannelGroup *ff_psy_find_group(FFPsyContext *ctx, int channel)
{
    int i = 0, ch = 0;

    while (ch <= channel)
        ch += ctx->group[i++].num_ch;

    return &ctx->group[i-1];
}