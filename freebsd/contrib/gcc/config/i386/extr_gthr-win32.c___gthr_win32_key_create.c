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
typedef  int __gthread_key_t ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ GetLastError () ; 
 int TlsAlloc () ; 
 int __mingwthr_key_dtor (int,void (*) (void*)) ; 

int
__gthr_win32_key_create (__gthread_key_t *key, void (*dtor) (void *))
{
  int status = 0;
  DWORD tls_index = TlsAlloc ();
  if (tls_index != 0xFFFFFFFF)
    {
      *key = tls_index;
#ifdef MINGW32_SUPPORTS_MT_EH
      /* Mingw runtime will run the dtors in reverse order for each thread
         when the thread exits.  */
      status = __mingwthr_key_dtor (*key, dtor);
#endif
    }
  else
    status = (int) GetLastError ();
  return status;
}