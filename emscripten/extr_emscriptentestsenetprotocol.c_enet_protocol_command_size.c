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
typedef  size_t enet_uint8 ;

/* Variables and functions */
 size_t ENET_PROTOCOL_COMMAND_MASK ; 
 size_t* commandSizes ; 

size_t
enet_protocol_command_size (enet_uint8 commandNumber)
{
    return commandSizes [commandNumber & ENET_PROTOCOL_COMMAND_MASK];
}