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
struct TYPE_2__ {int* bram; } ;

/* Variables and functions */
 TYPE_1__ scd ; 

__attribute__((used)) static unsigned int bram_read_word(unsigned int address)
{
  return (scd.bram[(address >> 1) & 0x1fff] | 0xff00);
}