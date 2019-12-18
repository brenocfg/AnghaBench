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
 int /*<<< orphan*/  HCI_HOST_BUFFER_SIZE ; 
 int /*<<< orphan*/  UINT16_TO_STREAM (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT8_TO_STREAM (int*,int) ; 
 int /*<<< orphan*/ * make_command (int /*<<< orphan*/ ,int const,int**) ; 

__attribute__((used)) static BT_HDR *make_host_buffer_size(uint16_t acl_size, uint8_t sco_size, uint16_t acl_count, uint16_t sco_count)
{
    uint8_t *stream;
    const uint8_t parameter_size = 2 + 1 + 2 + 2; // from each of the parameters
    BT_HDR *packet = make_command(HCI_HOST_BUFFER_SIZE, parameter_size, &stream);

    UINT16_TO_STREAM(stream, acl_size);
    UINT8_TO_STREAM(stream, sco_size);
    UINT16_TO_STREAM(stream, acl_count);
    UINT16_TO_STREAM(stream, sco_count);
    return packet;
}