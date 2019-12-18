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
typedef  int /*<<< orphan*/  __u32 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ IN_CLASSA (int /*<<< orphan*/ ) ; 
 scalar_t__ IN_CLASSB (int /*<<< orphan*/ ) ; 
 scalar_t__ IN_CLASSC (int /*<<< orphan*/ ) ; 
 scalar_t__ ipv4_is_zeronet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ int inet_abc_len(__be32 addr)
{
	int rc = -1;	/* Something else, probably a multicast. */

	if (ipv4_is_zeronet(addr))
		rc = 0;
	else {
		__u32 haddr = ntohl(addr);

		if (IN_CLASSA(haddr))
			rc = 8;
		else if (IN_CLASSB(haddr))
			rc = 16;
		else if (IN_CLASSC(haddr))
			rc = 24;
	}

	return rc;
}