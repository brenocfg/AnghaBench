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
typedef  int uint32_t ;

/* Variables and functions */
 int g_num_waitqs ; 
 int jenkins_hash (char*,size_t) ; 

__attribute__((used)) static __inline__ uint32_t waitq_hash(char *key, size_t length)
{
	uint32_t hash = jenkins_hash(key, length);

	hash &= (g_num_waitqs - 1);
	return hash;
}