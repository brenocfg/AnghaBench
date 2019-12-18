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
typedef  int uint32 ;
typedef  int uint16 ;
struct TYPE_2__ {scalar_t__ ram; } ;

/* Variables and functions */
 TYPE_1__ action_replay ; 

__attribute__((used)) static void ar_write_ram_8(uint32 address, uint32 data)
{
  /* byte writes are handled as word writes, with LSB duplicated in MSB (/LWR is not used) */
  *(uint16 *)(action_replay.ram + (address & 0xfffe)) = (data | (data << 8));
}