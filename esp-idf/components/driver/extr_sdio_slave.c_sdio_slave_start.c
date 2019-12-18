#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ esp_err_t ;
struct TYPE_6__ {int sdio_ioready1; } ;
struct TYPE_8__ {TYPE_2__ cfg_data1; } ;
struct TYPE_5__ {int /*<<< orphan*/  val; } ;
struct TYPE_7__ {TYPE_1__ slc0_int_clr; } ;

/* Variables and functions */
 scalar_t__ ESP_OK ; 
 TYPE_4__ HINF ; 
 TYPE_3__ HOST ; 
 int /*<<< orphan*/  UINT32_MAX ; 
 scalar_t__ recv_start () ; 
 scalar_t__ send_start () ; 

esp_err_t sdio_slave_start(void)
{
    esp_err_t ret;
    HOST.slc0_int_clr.val = UINT32_MAX;//clear all interrupts
    ret = send_start();
    if (ret != ESP_OK) return ret;
    ret = recv_start();
    if (ret != ESP_OK) return ret;
    HINF.cfg_data1.sdio_ioready1 = 1;   //set IO ready to 1 to allow host to use
    return ESP_OK;
}