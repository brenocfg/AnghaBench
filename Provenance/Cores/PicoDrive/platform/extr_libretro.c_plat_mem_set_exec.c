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
 int /*<<< orphan*/  PAGE_EXECUTE_READWRITE ; 
 int PROT_EXEC ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int VirtualProtect (void*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  lprintf (char*,void*,size_t,int /*<<< orphan*/ ) ; 
 int mprotect (void*,size_t,int) ; 

int plat_mem_set_exec(void *ptr, size_t size)
{
#ifdef _WIN32
   int ret = VirtualProtect(ptr,size,PAGE_EXECUTE_READWRITE,0);
   if (ret == 0)
      lprintf("mprotect(%p, %zd) failed: %d\n", ptr, size, 0);
#else
   int ret = mprotect(ptr, size, PROT_READ | PROT_WRITE | PROT_EXEC);
   if (ret != 0)
      lprintf("mprotect(%p, %zd) failed: %d\n", ptr, size, errno);
#endif
	return ret;
}