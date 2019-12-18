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
typedef  scalar_t__ sdio_slave_buf_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int /*<<< orphan*/  buf_desc_t ;
struct TYPE_2__ {int /*<<< orphan*/  recv_reg_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_HANDLE_IDLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ context ; 
 int /*<<< orphan*/  critical_enter_recv () ; 
 int /*<<< orphan*/  critical_exit_recv () ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  te ; 

esp_err_t sdio_slave_recv_unregister_buf(sdio_slave_buf_handle_t handle)
{
    buf_desc_t *desc = (buf_desc_t*)handle;
    CHECK_HANDLE_IDLE(desc); //in the queue, fail.

    critical_enter_recv();
    TAILQ_REMOVE(&context.recv_reg_list, desc, te);
    critical_exit_recv();
    free(desc);
    return ESP_OK;
}