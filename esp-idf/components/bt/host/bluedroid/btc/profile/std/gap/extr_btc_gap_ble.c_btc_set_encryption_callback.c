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
typedef  int /*<<< orphan*/  tBTA_TRANSPORT ;
typedef  int /*<<< orphan*/  tBTA_STATUS ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_TRACE_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btc_set_encryption_callback(BD_ADDR bd_addr, tBTA_TRANSPORT transport, tBTA_STATUS enc_status)
{
    UNUSED(bd_addr);
    UNUSED(transport);
    BTC_TRACE_DEBUG("enc_status = %x\n", enc_status);
    return;
}