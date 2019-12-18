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
struct timespec {int tv_sec; int tv_nsec; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 void* htonl (int) ; 

__attribute__((used)) static inline __be32*
xdr_encode_time(__be32 *p, struct timespec *timep)
{
	*p++ = htonl(timep->tv_sec);
	/* Convert nanoseconds into microseconds */
	*p++ = htonl(timep->tv_nsec ? timep->tv_nsec / 1000 : 0);
	return p;
}