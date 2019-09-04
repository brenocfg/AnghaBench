#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* oc; TYPE_1__* avctx; } ;
struct TYPE_7__ {scalar_t__ status; int /*<<< orphan*/  layout_map_tags; int /*<<< orphan*/  layout_map; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  channels; } ;
struct TYPE_6__ {int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  channels; } ;
typedef  TYPE_3__ AACContext ;

/* Variables and functions */
 scalar_t__ OC_LOCKED ; 
 scalar_t__ OC_NONE ; 
 int /*<<< orphan*/  output_configure (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pop_output_configuration(AACContext *ac) {
    if (ac->oc[1].status != OC_LOCKED && ac->oc[0].status != OC_NONE) {
        ac->oc[1] = ac->oc[0];
        ac->avctx->channels = ac->oc[1].channels;
        ac->avctx->channel_layout = ac->oc[1].channel_layout;
        output_configure(ac, ac->oc[1].layout_map, ac->oc[1].layout_map_tags,
                         ac->oc[1].status, 0);
    }
}