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

/* Variables and functions */
 int PROT_EXEC ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  _SC_PAGESIZE ; 
 scalar_t__ co_swap_function ; 
 int /*<<< orphan*/  mprotect (void*,unsigned long,int) ; 
 unsigned long sysconf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void co_init(void)
{
   unsigned long addr = (unsigned long)co_swap_function;
   unsigned long base = addr - (addr % sysconf(_SC_PAGESIZE));
   unsigned long size = (addr - base) + sizeof co_swap_function;
   mprotect((void*)base, size, PROT_READ | PROT_WRITE | PROT_EXEC);
}