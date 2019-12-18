#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint16 ;
struct TYPE_4__ {unsigned int* lut_offset; } ;
struct TYPE_3__ {scalar_t__* word_ram; } ;

/* Variables and functions */
 TYPE_2__ gfx ; 
 TYPE_1__ scd ; 

unsigned int cell_ram_1_read16(unsigned int address)
{
  address = gfx.lut_offset[(address >> 2) & 0x7fff] | (address & 0x10002);
  return *(uint16 *)(scd.word_ram[1] + address);
}