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
 int /*<<< orphan*/  callback_thread ; 
 int sceKernelCreateThread (char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceKernelStartThread (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int setup_callback(void)
{
   int thread_id = sceKernelCreateThread("update_thread",
         callback_thread, 0x11, 0xFA0, 0, 0);

   if (thread_id >= 0)
      sceKernelStartThread(thread_id, 0, 0);

   return thread_id;
}