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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLUFI_BUILD_TYPE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BLUFI_TYPE_CTRL ; 
 int /*<<< orphan*/  BLUFI_TYPE_CTRL_SUBTYPE_ACK ; 
 int /*<<< orphan*/  btc_blufi_send_encap (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void btc_blufi_send_ack(uint8_t seq)
{
    uint8_t type;
    uint8_t data;

    type = BLUFI_BUILD_TYPE(BLUFI_TYPE_CTRL, BLUFI_TYPE_CTRL_SUBTYPE_ACK);
    data = seq;

    btc_blufi_send_encap(type, &data, 1);
}