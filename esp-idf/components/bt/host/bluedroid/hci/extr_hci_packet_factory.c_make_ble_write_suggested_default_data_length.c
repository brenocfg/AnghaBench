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
 int /*<<< orphan*/  HCI_BLE_WRITE_DEFAULT_DATA_LENGTH ; 
 int /*<<< orphan*/  UINT16_TO_STREAM (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * make_command (int /*<<< orphan*/ ,int,int**) ; 

__attribute__((used)) static BT_HDR *make_ble_write_suggested_default_data_length(uint16_t SuggestedMaxTxOctets, uint16_t SuggestedMaxTxTime)
{
    uint8_t *stream;
    uint8_t parameter_size = sizeof(uint16_t) + sizeof(uint16_t);
    BT_HDR *packet = make_command(HCI_BLE_WRITE_DEFAULT_DATA_LENGTH, parameter_size, &stream);

    UINT16_TO_STREAM(stream, SuggestedMaxTxOctets);
    UINT16_TO_STREAM(stream, SuggestedMaxTxTime);
    return packet;
}