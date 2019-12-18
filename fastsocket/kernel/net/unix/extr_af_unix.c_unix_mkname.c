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
struct sockaddr_un {scalar_t__ sun_family; scalar_t__* sun_path; } ;

/* Variables and functions */
 scalar_t__ AF_UNIX ; 
 int EINVAL ; 
 int /*<<< orphan*/  csum_partial (struct sockaddr_un*,int,int /*<<< orphan*/ ) ; 
 int strlen (scalar_t__*) ; 
 unsigned int unix_hash_fold (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int unix_mkname(struct sockaddr_un *sunaddr, int len, unsigned *hashp)
{
	if (len <= sizeof(short) || len > sizeof(*sunaddr))
		return -EINVAL;
	if (!sunaddr || sunaddr->sun_family != AF_UNIX)
		return -EINVAL;
	if (sunaddr->sun_path[0]) {
		/*
		 * This may look like an off by one error but it is a bit more
		 * subtle. 108 is the longest valid AF_UNIX path for a binding.
		 * sun_path[108] doesnt as such exist.  However in kernel space
		 * we are guaranteed that it is a valid memory location in our
		 * kernel address buffer.
		 */
		((char *)sunaddr)[len] = 0;
		len = strlen(sunaddr->sun_path)+1+sizeof(short);
		return len;
	}

	*hashp = unix_hash_fold(csum_partial(sunaddr, len, 0));
	return len;
}