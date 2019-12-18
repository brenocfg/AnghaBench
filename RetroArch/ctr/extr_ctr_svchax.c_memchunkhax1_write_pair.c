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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int /*<<< orphan*/  MEMOP_ALLOC_LINEAR ; 
 int /*<<< orphan*/  MEMOP_FREE ; 
 int MEMPERM_READ ; 
 int MEMPERM_WRITE ; 
 int /*<<< orphan*/  gspwn (scalar_t__,scalar_t__,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svcControlMemory (scalar_t__*,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void memchunkhax1_write_pair(u32 val1, u32 val2)
{
   u32 linear_buffer;
   u8* flush_buffer;
   u32 tmp;

   u32* next_ptr3;
   u32* prev_ptr3;

   u32* next_ptr1;
   u32* prev_ptr6;

   svcControlMemory(&linear_buffer, 0, 0, 0x10000, MEMOP_ALLOC_LINEAR, MEMPERM_READ | MEMPERM_WRITE);

   flush_buffer = (u8*)(linear_buffer + 0x8000);

   svcControlMemory(&tmp, linear_buffer + 0x1000, 0, 0x1000, MEMOP_FREE, 0);
   svcControlMemory(&tmp, linear_buffer + 0x3000, 0, 0x2000, MEMOP_FREE, 0);
   svcControlMemory(&tmp, linear_buffer + 0x6000, 0, 0x1000, MEMOP_FREE, 0);

   next_ptr1 = (u32*)(linear_buffer + 0x0004);
   gspwn(linear_buffer + 0x0000, linear_buffer + 0x1000, 16, flush_buffer);

   next_ptr3 = (u32*)(linear_buffer + 0x2004);
   prev_ptr3 = (u32*)(linear_buffer + 0x2008);
   gspwn(linear_buffer + 0x2000, linear_buffer + 0x3000, 16, flush_buffer);

   prev_ptr6 = (u32*)(linear_buffer + 0x5008);
   gspwn(linear_buffer + 0x5000, linear_buffer + 0x6000, 16, flush_buffer);

   *next_ptr1 = *next_ptr3;
   *prev_ptr6 = *prev_ptr3;

   *prev_ptr3 = val1 - 4;
   *next_ptr3 = val2;
   gspwn(linear_buffer + 0x3000, linear_buffer + 0x2000, 16, flush_buffer);
   svcControlMemory(&tmp, 0, 0, 0x2000, MEMOP_ALLOC_LINEAR, MEMPERM_READ | MEMPERM_WRITE);

   gspwn(linear_buffer + 0x1000, linear_buffer + 0x0000, 16, flush_buffer);
   gspwn(linear_buffer + 0x6000, linear_buffer + 0x5000, 16, flush_buffer);

   svcControlMemory(&tmp, linear_buffer + 0x0000, 0, 0x1000, MEMOP_FREE, 0);
   svcControlMemory(&tmp, linear_buffer + 0x2000, 0, 0x4000, MEMOP_FREE, 0);
   svcControlMemory(&tmp, linear_buffer + 0x7000, 0, 0x9000, MEMOP_FREE, 0);

}