#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  DR; } ;

/* Variables and functions */
 TYPE_1__* CRC ; 
 scalar_t__ CRC_BASE ; 

uint32_t CRC_CalcCRC8bits(uint8_t CRC_Data)
{
  *(uint8_t*)(CRC_BASE) = (uint8_t) CRC_Data;

  return (CRC->DR);
}