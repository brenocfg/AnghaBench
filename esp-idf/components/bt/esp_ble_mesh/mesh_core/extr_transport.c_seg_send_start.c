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
typedef  int /*<<< orphan*/  u16_t ;
struct seg_tx {int /*<<< orphan*/  retransmit; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEG_RETRANSMIT_TIMEOUT (struct seg_tx*) ; 
 int /*<<< orphan*/  k_delayed_work_submit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void seg_send_start(u16_t duration, int err, void *user_data)
{
    struct seg_tx *tx = user_data;

    /* If there's an error in transmitting the 'sent' callback will never
     * be called. Make sure that we kick the retransmit timer also in this
     * case since otherwise we risk the transmission of becoming stale.
     */
    if (err) {
        k_delayed_work_submit(&tx->retransmit,
                              SEG_RETRANSMIT_TIMEOUT(tx));
    }
}