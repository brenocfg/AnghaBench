#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_5__ {void* pkt_len; scalar_t__ length; } ;
typedef  TYPE_1__ buf_desc_t ;
struct TYPE_6__ {int /*<<< orphan*/  sendbuf; TYPE_1__* in_flight; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  SDIO_SLAVE_CHECK (int,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* STAILQ_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ STATE_IDLE ; 
 TYPE_2__ context ; 
 int /*<<< orphan*/  qe ; 
 scalar_t__ sdio_ringbuf_peek_front (int /*<<< orphan*/ *) ; 
 scalar_t__ sdio_ringbuf_peek_rear (int /*<<< orphan*/ *) ; 
 scalar_t__ send_get_state () ; 
 int /*<<< orphan*/  send_length_write (int /*<<< orphan*/ ) ; 

__attribute__((used)) static esp_err_t send_reset_counter(void)
{
    SDIO_SLAVE_CHECK(send_get_state() == STATE_IDLE,
        "reset counter when transmission started", ESP_ERR_INVALID_STATE);

    send_length_write(0);

    uint32_t last_cnt=0;
    buf_desc_t *desc = context.in_flight;
    buf_desc_t *last = NULL;
    while(desc != NULL) {
        last_cnt += desc->length;
        desc->pkt_len = last_cnt;
        last = desc;
        desc = STAILQ_NEXT(desc, qe);
    }
    // in theory the desc should be the one right next to the last of in_flight,
    // but the link of last is NULL, so get the desc from the ringbuf directly.
    desc = (buf_desc_t*)sdio_ringbuf_peek_front(&context.sendbuf);
    while(desc != NULL) {
        last_cnt += desc->length;
        desc->pkt_len = last_cnt;
        last = desc;
        desc = STAILQ_NEXT(desc, qe);
    }
    if (last == NULL) {
        last = (buf_desc_t*)sdio_ringbuf_peek_rear(&context.sendbuf);
        last->pkt_len = 0;
    }

    return ESP_OK;
}