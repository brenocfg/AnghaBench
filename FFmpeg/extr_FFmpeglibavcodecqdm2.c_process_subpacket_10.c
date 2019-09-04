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
struct TYPE_5__ {TYPE_1__* packet; } ;
struct TYPE_4__ {int size; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ QDM2SubPNode ;
typedef  int /*<<< orphan*/  QDM2Context ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  fill_tone_level_array (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_get_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  init_tone_level_dequantization (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void process_subpacket_10(QDM2Context *q, QDM2SubPNode *node)
{
    GetBitContext gb;

    if (node) {
        init_get_bits(&gb, node->packet->data, node->packet->size * 8);
        init_tone_level_dequantization(q, &gb);
        fill_tone_level_array(q, 1);
    } else {
        fill_tone_level_array(q, 0);
    }
}