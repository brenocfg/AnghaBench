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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_VENDOR_BLE_SET_ADV_FLOW_CONTROL ; 
 int /*<<< orphan*/  UINT16_TO_STREAM (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT8_TO_STREAM (int*,int) ; 
 int /*<<< orphan*/ * make_command (int /*<<< orphan*/ ,int const,int**) ; 

__attribute__((used)) static BT_HDR *make_set_adv_report_flow_control(uint8_t enable, uint16_t num, uint16_t lost_threshold)
{
    uint8_t *stream;
    const uint8_t parameter_size = 1 + 2 + 2;
    BT_HDR *packet = make_command(HCI_VENDOR_BLE_SET_ADV_FLOW_CONTROL, parameter_size, &stream);

    UINT8_TO_STREAM(stream, enable);
    UINT16_TO_STREAM(stream, num);
    UINT16_TO_STREAM(stream, lost_threshold);
    return packet;
}