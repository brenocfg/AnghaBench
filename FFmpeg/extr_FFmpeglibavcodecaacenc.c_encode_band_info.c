#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  lambda; TYPE_1__* coder; } ;
struct TYPE_12__ {int num_windows; scalar_t__* group_len; } ;
struct TYPE_13__ {TYPE_2__ ics; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* encode_window_bands_info ) (TYPE_4__*,TYPE_3__*,int,scalar_t__,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_special_band_scalefactors ) (TYPE_4__*,TYPE_3__*) ;} ;
typedef  TYPE_3__ SingleChannelElement ;
typedef  TYPE_4__ AACEncContext ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,TYPE_3__*,int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void encode_band_info(AACEncContext *s, SingleChannelElement *sce)
{
    int w;

    if (s->coder->set_special_band_scalefactors)
        s->coder->set_special_band_scalefactors(s, sce);

    for (w = 0; w < sce->ics.num_windows; w += sce->ics.group_len[w])
        s->coder->encode_window_bands_info(s, sce, w, sce->ics.group_len[w], s->lambda);
}