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

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int res_query (char*,int,int,unsigned char*,int) ; 
 size_t strnlen (char const*,int) ; 

int res_querydomain(const char *name, const char *domain, int class, int type, unsigned char *dest, int len)
{
	char tmp[255];
	size_t nl = strnlen(name, 255);
	size_t dl = strnlen(domain, 255);
	if (nl+dl+1 > 254) return -1;
	memcpy(tmp, name, nl);
	tmp[nl] = '.';
	memcpy(tmp+nl+1, domain, dl+1);
	return res_query(tmp, class, type, dest, len);
}