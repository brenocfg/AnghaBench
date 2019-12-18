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
typedef  int /*<<< orphan*/  buffer_t ;

/* Variables and functions */
 scalar_t__ Curl_thread_buffer ; 
 scalar_t__ buffer_threaded ; 
 scalar_t__ buffer_undef ; 
 int /*<<< orphan*/ * locbufs ; 
 int /*<<< orphan*/ * pthread_getspecific (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_key_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_setspecific (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  thdbufdestroy (void*) ; 
 int /*<<< orphan*/  thdkey ; 

__attribute__((used)) static void
terminate(void)

{
  if(Curl_thread_buffer == buffer_threaded) {
    locbufs = pthread_getspecific(thdkey);
    pthread_setspecific(thdkey, (void *) NULL);
    pthread_key_delete(thdkey);
    }

  if(Curl_thread_buffer != buffer_undef) {
    thdbufdestroy((void *) locbufs);
    locbufs = (buffer_t *) NULL;
    }

  Curl_thread_buffer = buffer_undef;
}