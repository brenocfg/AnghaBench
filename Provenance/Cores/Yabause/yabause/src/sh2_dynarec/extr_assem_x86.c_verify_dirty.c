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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ pointer ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcmp (void*,void*,scalar_t__) ; 

int verify_dirty(pointer addr)
{
  u8 *ptr=(u8 *)addr;
  assert(ptr[5]==0xB8);
  u32 source=*(u32 *)(ptr+6);
  u32 copy=*(u32 *)(ptr+11);
  u32 len=*(u32 *)(ptr+16);
  assert(ptr[20]==0xE8); // call instruction
  return !memcmp((void *)source,(void *)copy,len);
}