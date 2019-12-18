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
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline __be32*
xdr_decode_time(__be32 *p, struct timespec *timep)
{
	timep->tv_sec = ntohl(*p++);
	/* Convert microseconds into nanoseconds */
	timep->tv_nsec = ntohl(*p++) * 1000;
	return p;
}