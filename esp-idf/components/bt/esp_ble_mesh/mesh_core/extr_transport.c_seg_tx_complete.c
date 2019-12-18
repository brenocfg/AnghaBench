#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct seg_tx {int /*<<< orphan*/  cb_data; TYPE_1__* cb; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* end ) (int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  seg_tx_reset (struct seg_tx*) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void seg_tx_complete(struct seg_tx *tx, int err)
{
    if (tx->cb && tx->cb->end) {
        tx->cb->end(err, tx->cb_data);
    }

    seg_tx_reset(tx);
}