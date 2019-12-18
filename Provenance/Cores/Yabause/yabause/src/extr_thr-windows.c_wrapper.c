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
struct thd_s {int /*<<< orphan*/  mutex; int /*<<< orphan*/  arg; int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TlsSetValue (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  hnd_key ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static DWORD wrapper(void *hnd) 
{
   struct thd_s *hnds = (struct thd_s *)hnd;

   EnterCriticalSection(&hnds->mutex);

   /* Set the handle for the thread, and call the actual thread function. */
   TlsSetValue(hnd_key, hnd);
   hnds->func(hnds->arg);

   LeaveCriticalSection(&hnds->mutex);

   return 0;
}