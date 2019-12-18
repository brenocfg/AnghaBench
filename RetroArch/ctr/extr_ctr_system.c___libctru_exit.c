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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  MEMOP_FREE ; 
 int /*<<< orphan*/  __heapBase ; 
 scalar_t__ __heap_size ; 
 int /*<<< orphan*/  __linear_heap ; 
 scalar_t__ __linear_heap_size ; 
 int /*<<< orphan*/  __stack_bottom ; 
 scalar_t__ __stack_size_extra ; 
 int /*<<< orphan*/  __sync_fini () ; 
 scalar_t__ __system_argv ; 
 int /*<<< orphan*/  __system_retAddr () ; 
 int /*<<< orphan*/  envDestroyHandles () ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  svcControlMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  svcExitProcess () ; 

void __attribute__((noreturn)) __libctru_exit(int rc)
{
   u32 tmp = 0;

   if (__system_argv)
      free(__system_argv);

   /* Unmap the linear heap */
   svcControlMemory(&tmp, __linear_heap, 0x0, __linear_heap_size, MEMOP_FREE, 0x0);

   /* Unmap the application heap */
   svcControlMemory(&tmp, __heapBase, 0x0, __heap_size, MEMOP_FREE, 0x0);

   if (__stack_size_extra)
      svcControlMemory(&tmp, __stack_bottom, 0x0, __stack_size_extra, MEMOP_FREE, 0x0);

   /* Close some handles */
   envDestroyHandles();

   if (__sync_fini)
      __sync_fini();

   /* Jump to the loader if it provided a callback */
   if (__system_retAddr)
      __system_retAddr();

   /* Since above did not jump, end this process */
   svcExitProcess();
}