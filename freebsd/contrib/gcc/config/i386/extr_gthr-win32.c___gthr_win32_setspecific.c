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
typedef  int /*<<< orphan*/  __gthread_key_t ;

/* Variables and functions */
 scalar_t__ GetLastError () ; 
 scalar_t__ TlsSetValue (int /*<<< orphan*/ ,void*) ; 

int
__gthr_win32_setspecific (__gthread_key_t key, const void *ptr)
{
  return (TlsSetValue (key, (void*) ptr) != 0) ? 0 : (int) GetLastError ();
}