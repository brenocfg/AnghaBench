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
typedef  unsigned long* cothread_t ;

/* Variables and functions */
 int /*<<< orphan*/  co_active_buffer ; 
 int /*<<< orphan*/ * co_active_handle ; 
 int /*<<< orphan*/  co_init () ; 
 int /*<<< orphan*/  co_swap ; 
 scalar_t__ malloc (unsigned int) ; 

cothread_t co_create(unsigned int size, void(*entrypoint)(void))
   {
      unsigned long* handle = 0;
      if (!co_swap)
         co_init();
      if (!co_active_handle) co_active_handle = &co_active_buffer;
      size += 256;
      size &= ~15;

      if ((handle = (unsigned long*)malloc(size)))
      {
         unsigned long* p = (unsigned long*)((unsigned char*)handle + size);
         handle[8] = (unsigned long)p;
         handle[9] = (unsigned long)entrypoint;
      }

      return handle;
   }