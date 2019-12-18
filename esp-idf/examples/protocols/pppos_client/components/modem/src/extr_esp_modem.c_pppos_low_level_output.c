#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ppp_pcb ;
struct TYPE_3__ {int /*<<< orphan*/  (* send_data ) (TYPE_1__*,char const*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ modem_dte_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t pppos_low_level_output(ppp_pcb *pcb, uint8_t *data, uint32_t len, void *ctx)
{
    modem_dte_t *dte = (modem_dte_t *)ctx;
    return dte->send_data(dte, (const char *)data, len);
}