#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ sdio_ioready1; } ;
struct TYPE_4__ {TYPE_1__ cfg_data1; } ;

/* Variables and functions */
 TYPE_2__ HINF ; 
 int /*<<< orphan*/  recv_stop () ; 
 int /*<<< orphan*/  send_stop () ; 

void sdio_slave_stop(void)
{
    HINF.cfg_data1.sdio_ioready1 = 0;   //set IO ready to 1 to stop host from using
    send_stop();
    recv_stop();
}