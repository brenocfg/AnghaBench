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
struct TYPE_4__ {int /*<<< orphan*/ * cache; } ;
typedef  TYPE_1__ VP9BSFContext ;
struct TYPE_5__ {TYPE_1__* priv_data; } ;
typedef  TYPE_2__ AVBSFContext ;

/* Variables and functions */
 int MAX_CACHE ; 
 int /*<<< orphan*/  av_packet_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vp9_superframe_close(AVBSFContext *ctx)
{
    VP9BSFContext *s = ctx->priv_data;
    int n;

    // free cached data
    for (n = 0; n < MAX_CACHE; n++)
        av_packet_free(&s->cache[n]);
}