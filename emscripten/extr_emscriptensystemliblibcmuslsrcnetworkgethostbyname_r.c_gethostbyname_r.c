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
struct hostent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int gethostbyname2_r (char const*,int /*<<< orphan*/ ,struct hostent*,char*,size_t,struct hostent**,int*) ; 

int gethostbyname_r(const char *name,
	struct hostent *h, char *buf, size_t buflen,
	struct hostent **res, int *err)
{
	return gethostbyname2_r(name, AF_INET, h, buf, buflen, res, err);
}