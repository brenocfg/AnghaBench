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
struct passwd {int dummy; } ;

/* Variables and functions */
 char* getlogin () ; 
 struct passwd* getpwnam (char const*) ; 

__attribute__((used)) static struct passwd *
getpwlogin(void)
{
	const char *login;

	login = getlogin();
	if (login == NULL)
		return (NULL);

	return (getpwnam(login));
}