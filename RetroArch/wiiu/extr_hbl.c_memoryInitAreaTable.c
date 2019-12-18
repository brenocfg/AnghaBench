#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int end_address; scalar_t__ start_address; } ;
typedef  TYPE_1__ memory_values_t ;

/* Variables and functions */
 scalar_t__ getApplicationEndAddr () ; 
 TYPE_1__* mem_vals_540 ; 
 int /*<<< orphan*/  memoryAddArea (scalar_t__,int,int) ; 

__attribute__((used)) static void memoryInitAreaTable(u32 args_size)
{
    u32 ApplicationMemoryEnd = (u32)getApplicationEndAddr() + args_size;

    /* This one seems to be available on every firmware and therefore its our code area but also our main RPX area behind our code */
    /* 22876 kB - our application      ok  */
    memoryAddArea(ApplicationMemoryEnd + 0x30000000, 0x30000000 + 0x01E20000, 0);

    const memory_values_t * mem_vals = mem_vals_540;

    /* Fill entries */
    int i = 0;
    while (mem_vals[i].start_address)
    {
        memoryAddArea(mem_vals[i].start_address, mem_vals[i].end_address, i + 1);
        i++;
    }
}