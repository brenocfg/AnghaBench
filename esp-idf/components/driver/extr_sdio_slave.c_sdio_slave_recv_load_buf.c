#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ sdio_slave_buf_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int /*<<< orphan*/  buf_stailq_t ;
struct TYPE_10__ {int owner; scalar_t__ not_receiving; } ;
typedef  TYPE_2__ buf_desc_t ;
struct TYPE_9__ {int start; int restart; scalar_t__ addr; } ;
struct TYPE_12__ {TYPE_1__ slc0_tx_link; } ;
struct TYPE_11__ {TYPE_2__* recv_cur_ret; int /*<<< orphan*/  recv_reg_list; int /*<<< orphan*/  recv_link_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_HANDLE_IDLE (TYPE_2__*) ; 
 int /*<<< orphan*/  ESP_LOGV (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_7__ SLC ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ * const,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* STAILQ_LAST (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (scalar_t__) ; 
 int /*<<< orphan*/  buf_desc_s ; 
 TYPE_3__ context ; 
 int /*<<< orphan*/  critical_enter_recv () ; 
 int /*<<< orphan*/  critical_exit_recv () ; 
 int /*<<< orphan*/  qe ; 
 int /*<<< orphan*/  recv_size_inc () ; 
 int /*<<< orphan*/  te ; 

esp_err_t sdio_slave_recv_load_buf(sdio_slave_buf_handle_t handle)
{
    buf_desc_t *desc = (buf_desc_t*)handle;
    CHECK_HANDLE_IDLE(desc);

    buf_stailq_t *const queue = &context.recv_link_list;

    critical_enter_recv();
    assert(desc->not_receiving);
    TAILQ_REMOVE(&context.recv_reg_list, desc, te);
    desc->owner = 1;
    desc->not_receiving = 0; //manually remove the prev link (by set not_receiving=0), to indicate this is in the queue

    buf_desc_t *const tail = STAILQ_LAST(queue, buf_desc_s, qe);

    STAILQ_INSERT_TAIL(queue, desc, qe);
    if (context.recv_cur_ret == NULL) {
        context.recv_cur_ret = desc;
    }

    if (tail == NULL) {
        //no one in the ll, start new ll operation.
        SLC.slc0_tx_link.addr = (uint32_t)desc;
        SLC.slc0_tx_link.start = 1;
        ESP_LOGV(TAG, "recv_load_buf: start new");
    } else {
        //restart former ll operation
        SLC.slc0_tx_link.restart = 1;
        ESP_LOGV(TAG, "recv_load_buf: restart");
    }
    critical_exit_recv();
    recv_size_inc();

    return ESP_OK;
}