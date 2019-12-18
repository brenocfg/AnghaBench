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
typedef  int /*<<< orphan*/  u16_t ;
struct seg_tx {int /*<<< orphan*/  cb_data; TYPE_1__* cb; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* start ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void seg_first_send_start(u16_t duration, int err, void *user_data)
{
    struct seg_tx *tx = user_data;

    if (tx->cb && tx->cb->start) {
        tx->cb->start(duration, err, tx->cb_data);
    }
}