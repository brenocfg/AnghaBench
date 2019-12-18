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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ sdio_slave_buf_handle_t ;
typedef  scalar_t__ portBASE_TYPE ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int /*<<< orphan*/  buf_stailq_t ;
struct TYPE_5__ {scalar_t__ owner; size_t length; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ buf_desc_t ;
typedef  int /*<<< orphan*/  TickType_t ;
struct TYPE_6__ {int /*<<< orphan*/  recv_reg_list; int /*<<< orphan*/  recv_link_list; int /*<<< orphan*/  recv_event; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_TIMEOUT ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  SDIO_SLAVE_CHECK (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* STAILQ_FIRST (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ * const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__ context ; 
 int /*<<< orphan*/  critical_enter_recv () ; 
 int /*<<< orphan*/  critical_exit_recv () ; 
 scalar_t__ pdFALSE ; 
 int /*<<< orphan*/  qe ; 
 int /*<<< orphan*/  te ; 
 scalar_t__ xSemaphoreTake (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

esp_err_t sdio_slave_recv(sdio_slave_buf_handle_t* handle_ret, uint8_t **out_addr, size_t *out_len, TickType_t wait)
{
    SDIO_SLAVE_CHECK(handle_ret != NULL, "handle address cannot be 0", ESP_ERR_INVALID_ARG);
    portBASE_TYPE ret = xSemaphoreTake(context.recv_event, wait);
    if (ret == pdFALSE) return ESP_ERR_TIMEOUT;

    buf_stailq_t *const queue = &context.recv_link_list;

    critical_enter_recv();
    //remove from queue, add back to reg list.
    buf_desc_t *desc = STAILQ_FIRST(queue);
    STAILQ_REMOVE_HEAD(queue, qe);
    TAILQ_INSERT_TAIL(&context.recv_reg_list, desc, te);
    critical_exit_recv();

    assert(desc != NULL && desc->owner == 0);
    *handle_ret = (sdio_slave_buf_handle_t)desc;
    if (out_addr) *out_addr = desc->buf;
    if (out_len) *out_len = desc->length;
    return ESP_OK;
}