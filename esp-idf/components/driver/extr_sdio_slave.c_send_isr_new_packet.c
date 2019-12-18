#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_6__ {int /*<<< orphan*/  pkt_len; } ;
typedef  TYPE_1__ buf_desc_t ;
struct TYPE_7__ {TYPE_1__* in_flight_end; TYPE_1__* in_flight; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_EARLY_LOGD (int /*<<< orphan*/ ,char*,TYPE_1__* const,TYPE_1__* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  STATE_SENDING ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_3__ context ; 
 int /*<<< orphan*/  send_length_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_set_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_start_transmission (TYPE_1__* const) ; 
 int /*<<< orphan*/  send_stop_ll_operation () ; 

__attribute__((used)) static inline esp_err_t send_isr_new_packet(void)
{
    // since eof is changed, we have to stop and reset the link list,
    // and restart new link list operation
    buf_desc_t *const start_desc = context.in_flight;
    buf_desc_t *const end_desc = context.in_flight_end;
    assert(start_desc != NULL && end_desc != NULL);

    send_stop_ll_operation();
    send_start_transmission(start_desc);

    // update pkt_len register to allow host reading.
    send_length_write(end_desc->pkt_len);

    send_set_state(STATE_SENDING);

    ESP_EARLY_LOGD(TAG, "restart new send: %p->%p, pkt_len: %d", start_desc, end_desc, end_desc->pkt_len);
    return ESP_OK;
}