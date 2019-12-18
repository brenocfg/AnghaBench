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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  btc_msg_t ;
typedef  int /*<<< orphan*/  bt_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BT_STATUS_BUSY ; 
 int /*<<< orphan*/  BT_STATUS_NOMEM ; 
 int /*<<< orphan*/  BT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  btc_thread ; 
 int /*<<< orphan*/  btc_thread_handler ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ osi_malloc (int) ; 
 int osi_thread_post (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bt_status_t btc_task_post(btc_msg_t *msg, uint32_t timeout)
{
    btc_msg_t *lmsg;

    lmsg = (btc_msg_t *)osi_malloc(sizeof(btc_msg_t));
    if (lmsg == NULL) {
        return BT_STATUS_NOMEM;
    }

    memcpy(lmsg, msg, sizeof(btc_msg_t));

    if (osi_thread_post(btc_thread, btc_thread_handler, lmsg, 0, timeout) == false) {
        return BT_STATUS_BUSY;
    }

    return BT_STATUS_SUCCESS;
}