#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u8_t ;
typedef  int u16_t ;
struct seg_tx {int seq_auth; int dst; scalar_t__ nack_count; scalar_t__ seg_n; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct seg_tx*) ; 
 struct seg_tx* seg_tx ; 

__attribute__((used)) static struct seg_tx *seg_tx_lookup(u16_t seq_zero, u8_t obo, u16_t addr)
{
    struct seg_tx *tx;
    int i;

    for (i = 0; i < ARRAY_SIZE(seg_tx); i++) {
        tx = &seg_tx[i];

        if ((tx->seq_auth & 0x1fff) != seq_zero) {
            continue;
        }

        if (tx->dst == addr) {
            return tx;
        }

        /* If the expected remote address doesn't match,
         * but the OBO flag is set and this is the first
         * acknowledgement, assume it's a Friend that's
         * responding and therefore accept the message.
         */
        if (obo && tx->nack_count == tx->seg_n + 1) {
            tx->dst = addr;
            return tx;
        }
    }

    return NULL;
}