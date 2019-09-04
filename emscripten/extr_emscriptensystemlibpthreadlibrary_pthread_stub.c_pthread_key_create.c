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
 scalar_t__ malloc (int) ; 

int pthread_key_create(pthread_key_t *key, void (*destructor)(void *))
{
	if (key == 0) return EINVAL;
	uintptr_t *tls = (uintptr_t *)malloc(sizeof(uintptr_t)*2);
	tls[0] = 0;
	tls[1] = PTHREAD_TLS_MAGIC_ID;
	*key = (pthread_key_t)tls;
	return 0;
}