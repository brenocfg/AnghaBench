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
typedef  int u32 ;
typedef  scalar_t__ pointer ;

/* Variables and functions */
 scalar_t__ BiosRom ; 
 scalar_t__ HighWram ; 
 scalar_t__ LowWram ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static pointer map_address(u32 address)
{
  if((address&0xDFF00000)==0x200000) return (pointer)LowWram+(address&0xFFFFF);
  if((address&0xDE000000)==0x6000000) return (pointer)HighWram+(address&0xFFFFF);
  assert((address&0xDFF00000)==0);
  return (pointer)BiosRom+(address&0x8FFFF);
}