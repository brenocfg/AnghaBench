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
struct TYPE_2__ {unsigned int instruction; } ;

/* Variables and functions */
 TYPE_1__ inst ; 

__attribute__((used)) static void
neon_write_immbits (unsigned immbits)
{
  inst.instruction |= immbits & 0xf;
  inst.instruction |= ((immbits >> 4) & 0x7) << 16;
  inst.instruction |= ((immbits >> 7) & 0x1) << 24;
}