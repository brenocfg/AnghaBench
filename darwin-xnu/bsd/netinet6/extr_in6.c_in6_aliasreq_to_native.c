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
struct in6_aliasreq_64 {int dummy; } ;
struct in6_aliasreq_32 {int dummy; } ;
struct in6_aliasreq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (void*,struct in6_aliasreq*,int) ; 
 int /*<<< orphan*/  in6_aliasreq_32_to_64 (struct in6_aliasreq_32*,struct in6_aliasreq_64*) ; 
 int /*<<< orphan*/  in6_aliasreq_64_to_32 (struct in6_aliasreq_64*,struct in6_aliasreq_32*) ; 

__attribute__((used)) static struct in6_aliasreq *
in6_aliasreq_to_native(void *data, int data_is_64, struct in6_aliasreq *dst)
{
#if defined(__LP64__)
	if (data_is_64)
		bcopy(data, dst, sizeof (*dst));
	else
		in6_aliasreq_32_to_64((struct in6_aliasreq_32 *)data,
		    (struct in6_aliasreq_64 *)dst);
#else
	if (data_is_64)
		in6_aliasreq_64_to_32((struct in6_aliasreq_64 *)data,
		    (struct in6_aliasreq_32 *)dst);
	else
		bcopy(data, dst, sizeof (*dst));
#endif /* __LP64__ */
	return (dst);
}