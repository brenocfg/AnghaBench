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
 int /*<<< orphan*/  MAXHOSTNAMELEN ; 
 void* miniwget2 (char*,unsigned short,char*,int*,char*,int,unsigned int,int*) ; 
 int /*<<< orphan*/  parseURL (char const*,char*,unsigned short*,char**,unsigned int*) ; 
 int /*<<< orphan*/  printf (char*,char*,unsigned short,char*,unsigned int) ; 

void *
miniwget_getaddr(const char * url, int * size,
                 char * addr, int addrlen, unsigned int scope_id,
                 int * status_code)
{
	unsigned short port;
	char * path;
	/* protocol://host:port/path */
	char hostname[MAXHOSTNAMELEN+1];
	*size = 0;
	if(addr)
		addr[0] = '\0';
	if(!parseURL(url, hostname, &port, &path, &scope_id))
		return NULL;
#ifdef DEBUG
	printf("parsed url : hostname='%s' port=%hu path='%s' scope_id=%u\n",
	       hostname, port, path, scope_id);
#endif
	return miniwget2(hostname, port, path, size, addr, addrlen, scope_id, status_code);
}