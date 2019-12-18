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
typedef  int /*<<< orphan*/  BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_READ_LOCAL_EXT_FEATURES ; 
 int /*<<< orphan*/  UINT8_TO_STREAM (int*,int) ; 
 int /*<<< orphan*/ * make_command (int /*<<< orphan*/ ,int const,int**) ; 

__attribute__((used)) static BT_HDR *make_read_local_extended_features(uint8_t page_number)
{
    uint8_t *stream;
    const uint8_t parameter_size = 1;
    BT_HDR *packet = make_command(HCI_READ_LOCAL_EXT_FEATURES, parameter_size, &stream);

    UINT8_TO_STREAM(stream, page_number);
    return packet;
}