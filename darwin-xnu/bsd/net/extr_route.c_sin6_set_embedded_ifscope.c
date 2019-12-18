#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * s6_addr16; } ;
struct TYPE_3__ {TYPE_2__ sin6_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_SIN6IFSCOPE (struct sockaddr*) ; 
 int /*<<< orphan*/  IN6_IS_SCOPE_EMBED (TYPE_2__*) ; 
 TYPE_1__* SIN6 (struct sockaddr*) ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (unsigned int) ; 

__attribute__((used)) static inline void
sin6_set_embedded_ifscope(struct sockaddr *sa, unsigned int ifscope)
{
	/* Caller must pass in sockaddr_in6 */
	ASSERT_SIN6IFSCOPE(sa);
	VERIFY(IN6_IS_SCOPE_EMBED(&(SIN6(sa)->sin6_addr)));

	SIN6(sa)->sin6_addr.s6_addr16[1] = htons(ifscope);
}