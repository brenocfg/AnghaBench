#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int sa_family; } ;
struct TYPE_2__ {int /*<<< orphan*/  sin6_addr; } ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 unsigned int IFSCOPE_NONE ; 
 scalar_t__ IN6_IS_SCOPE_EMBED (int /*<<< orphan*/ *) ; 
 struct sockaddr* SA (struct sockaddr_storage*) ; 
 TYPE_1__* SIN6 (struct sockaddr_storage*) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  bcopy (struct sockaddr*,struct sockaddr_storage*,int) ; 
 int /*<<< orphan*/  bzero (struct sockaddr_storage*,int) ; 
 unsigned int sin6_get_embedded_ifscope (struct sockaddr*) ; 
 unsigned int sin6_get_ifscope (struct sockaddr*) ; 
 int /*<<< orphan*/  sin6_set_embedded_ifscope (struct sockaddr*,unsigned int) ; 
 int /*<<< orphan*/  sin6_set_ifscope (struct sockaddr*,unsigned int) ; 
 unsigned int sin_get_ifscope (struct sockaddr*) ; 
 int /*<<< orphan*/  sin_set_ifscope (struct sockaddr*,unsigned int) ; 

struct sockaddr *
sa_copy(struct sockaddr *src, struct sockaddr_storage *dst,
    unsigned int *pifscope)
{
	int af = src->sa_family;
	unsigned int ifscope = (pifscope != NULL) ? *pifscope : IFSCOPE_NONE;

	VERIFY(af == AF_INET || af == AF_INET6);

	bzero(dst, sizeof (*dst));

	if (af == AF_INET) {
		bcopy(src, dst, sizeof (struct sockaddr_in));
		if (pifscope == NULL || ifscope != IFSCOPE_NONE)
			sin_set_ifscope(SA(dst), ifscope);
	} else {
		bcopy(src, dst, sizeof (struct sockaddr_in6));
		if (pifscope != NULL &&
		    IN6_IS_SCOPE_EMBED(&SIN6(dst)->sin6_addr)) {
			unsigned int eifscope;
			/*
			 * If the address contains the embedded scope ID,
			 * use that as the value for sin6_scope_id as long
			 * the caller doesn't insist on clearing it (by
			 * passing NULL) or setting it.
			 */
			eifscope = sin6_get_embedded_ifscope(SA(dst));
			if (eifscope != IFSCOPE_NONE && ifscope == IFSCOPE_NONE)
				ifscope = eifscope;
			if (ifscope != IFSCOPE_NONE) {
				/* Set ifscope from pifscope or eifscope */
				sin6_set_ifscope(SA(dst), ifscope);
			} else {
				/* If sin6_scope_id has a value, use that one */
				ifscope = sin6_get_ifscope(SA(dst));
			}
			/*
			 * If sin6_scope_id is set but the address doesn't
			 * contain the equivalent embedded value, set it.
			 */
			if (ifscope != IFSCOPE_NONE && eifscope != ifscope)
				sin6_set_embedded_ifscope(SA(dst), ifscope);
		} else if (pifscope == NULL || ifscope != IFSCOPE_NONE) {
			sin6_set_ifscope(SA(dst), ifscope);
		}
	}

	if (pifscope != NULL) {
		*pifscope = (af == AF_INET) ? sin_get_ifscope(SA(dst)) :
		    sin6_get_ifscope(SA(dst));
	}

	return (SA(dst));
}