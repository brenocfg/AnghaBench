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
 int /*<<< orphan*/  arch_get_random_long (unsigned long*) ; 
 int /*<<< orphan*/  extract_entropy (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,unsigned long*,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  nonblocking_pool ; 

void get_random_bytes(void *buf, int nbytes)
{
	char *p = buf;

	while (nbytes) {
		unsigned long v;
		int chunk = min(nbytes, (int)sizeof(unsigned long));
		
		if (!arch_get_random_long(&v))
			break;
		
		memcpy(p, &v, chunk);
		p += chunk;
		nbytes -= chunk;
	}

	extract_entropy(&nonblocking_pool, p, nbytes, 0, 0);
}