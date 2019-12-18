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
struct TYPE_6__ {TYPE_1__* priv_data; } ;
struct TYPE_5__ {int eos; int /*<<< orphan*/  max_ra; int /*<<< orphan*/  sei; } ;
typedef  TYPE_1__ HEVCContext ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  ff_hevc_flush_dpb (TYPE_1__*) ; 
 int /*<<< orphan*/  ff_hevc_reset_sei (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hevc_decode_flush(AVCodecContext *avctx)
{
    HEVCContext *s = avctx->priv_data;
    ff_hevc_flush_dpb(s);
    ff_hevc_reset_sei(&s->sei);
    s->max_ra = INT_MAX;
    s->eos = 1;
}