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
typedef  scalar_t__ uint_t ;

/* Variables and functions */
 scalar_t__ pthread_key_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_key_create_once_np (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_setspecific (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  uu_error_key ; 
 int uu_error_key_setup ; 
 int /*<<< orphan*/  uu_key_lock ; 

void
uu_set_error(uint_t code)
{

#if defined(PTHREAD_ONCE_KEY_NP)
	if (pthread_key_create_once_np(&uu_error_key, NULL) != 0)
		uu_error_key_setup = -1;
	else
		uu_error_key_setup = 1;
#else	/* PTHREAD_ONCE_KEY_NP */
	if (uu_error_key_setup == 0) {
		(void) pthread_mutex_lock(&uu_key_lock);
		if (uu_error_key_setup == 0) {
			if (pthread_key_create(&uu_error_key, NULL) != 0)
				uu_error_key_setup = -1;
			else
				uu_error_key_setup = 1;
		}
		(void) pthread_mutex_unlock(&uu_key_lock);
	}
#endif	/* PTHREAD_ONCE_KEY_NP */
	if (uu_error_key_setup > 0)
		(void) pthread_setspecific(uu_error_key,
		    (void *)(uintptr_t)code);
}