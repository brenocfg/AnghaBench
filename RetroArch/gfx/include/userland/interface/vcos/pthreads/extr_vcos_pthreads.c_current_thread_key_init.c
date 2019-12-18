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
 int /*<<< orphan*/  _vcos_thread_current_key ; 
 int _vcos_thread_current_key_created ; 
 int /*<<< orphan*/  pthread_key_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 int /*<<< orphan*/  vcos_dummy_thread_cleanup ; 

__attribute__((used)) static void current_thread_key_init(void)
{
   vcos_assert(!_vcos_thread_current_key_created);
   pthread_key_create (&_vcos_thread_current_key, vcos_dummy_thread_cleanup);
   _vcos_thread_current_key_created = 1;
}