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
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  in6_sin6_2_sin (struct sockaddr_in*,struct sockaddr_in6*) ; 

void
in6_sin6_2_sin_in_sock(struct sockaddr *nam)
{
	struct sockaddr_in *sin_p;
	struct sockaddr_in6 sin6;

	/*
	 * Save original sockaddr_in6 addr and convert it
	 * to sockaddr_in.
	 */
	sin6 = *(struct sockaddr_in6 *)(void *)nam;
	sin_p = (struct sockaddr_in *)(void *)nam;
	in6_sin6_2_sin(sin_p, &sin6);
}