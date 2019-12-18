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
struct TYPE_9__ {int /*<<< orphan*/  cm_table_select; int /*<<< orphan*/  superblocktype_2_3; int /*<<< orphan*/  nb_channels; int /*<<< orphan*/  coding_method; int /*<<< orphan*/  tone_level_idx_temp; int /*<<< orphan*/  tone_level_idx; } ;
struct TYPE_8__ {TYPE_1__* packet; } ;
struct TYPE_7__ {int size; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ QDM2SubPNode ;
typedef  TYPE_3__ QDM2Context ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  fill_coding_method_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_get_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  synthfilt_build_sb_samples (TYPE_3__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void process_subpacket_11(QDM2Context *q, QDM2SubPNode *node)
{
    GetBitContext gb;
    int length = 0;

    if (node) {
        length = node->packet->size * 8;
        init_get_bits(&gb, node->packet->data, length);
    }

    if (length >= 32) {
        int c = get_bits(&gb, 13);

        if (c > 3)
            fill_coding_method_array(q->tone_level_idx,
                                     q->tone_level_idx_temp, q->coding_method,
                                     q->nb_channels, 8 * c,
                                     q->superblocktype_2_3, q->cm_table_select);
    }

    synthfilt_build_sb_samples(q, &gb, length, 0, 8);
}