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
struct TYPE_5__ {TYPE_1__* priv_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  h2645_pkt; int /*<<< orphan*/  av1_pkt; } ;
typedef  TYPE_1__ ExtractExtradataContext ;
typedef  TYPE_2__ AVBSFContext ;

/* Variables and functions */
 int /*<<< orphan*/  ff_av1_packet_uninit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_h2645_packet_uninit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void extract_extradata_close(AVBSFContext *ctx)
{
    ExtractExtradataContext *s = ctx->priv_data;
    ff_av1_packet_uninit(&s->av1_pkt);
    ff_h2645_packet_uninit(&s->h2645_pkt);
}