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
typedef  scalar_t__ pthread_key_t ;

/* Variables and functions */
 int EINVAL ; 
 uintptr_t PTHREAD_TLS_MAGIC_ID ; 

int pthread_setspecific(pthread_key_t key, const void *value)
{
	uintptr_t *tls = (uintptr_t *)key;
	if (tls[1] != PTHREAD_TLS_MAGIC_ID)
		return EINVAL;
	tls[0] = (uintptr_t)value;
	return 0;
}