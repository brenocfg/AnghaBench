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
struct TYPE_2__ {int /*<<< orphan*/  rom; } ;

/* Variables and functions */
 int READ_BYTE (int /*<<< orphan*/ ,int) ; 
 TYPE_1__ cart ; 

__attribute__((used)) static uint32 mapper_t5740_r(uint32 address)
{
  /* By default, first 32K of each eight 512K pages mapped in $000000-$3FFFFF are mirrored in the 512K page   */
  /* mirroring is disabled/enabled when a specific number of words is being read from specific ROM addresses  */
  /* Exact decoding isn't known but mirrored data is expected on startup when reading a few times from $181xx */
  /* this area doesn't seem to be accessed as byte later so it seems safe to always return mirrored data here */
  if ((address & 0xff00) == 0x8100)
  {
    return READ_BYTE(cart.rom , (address & 0x7fff));
  }

  return READ_BYTE(cart.rom, address);
}