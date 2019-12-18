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
typedef  int /*<<< orphan*/  tmp ;

/* Variables and functions */
 int IF_NAMESIZE ; 
 scalar_t__ MAXHOSTNAMELEN ; 
 int /*<<< orphan*/  MIN (scalar_t__,int) ; 
 unsigned int if_nametoindex (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strstr (char const*,char*) ; 
 scalar_t__ strtoul (char*,int /*<<< orphan*/ *,int) ; 

int
parseURL(const char * url,
         char * hostname, unsigned short * port,
         char * * path, unsigned int * scope_id)
{
	char * p1, *p2, *p3;
	if(!url)
		return 0;
	p1 = (char*)strstr(url, "://");
	if(!p1)
		return 0;
	p1 += 3;
	if(  (url[0]!='h') || (url[1]!='t')
	   ||(url[2]!='t') || (url[3]!='p'))
		return 0;
	memset(hostname, 0, MAXHOSTNAMELEN + 1);
	if(*p1 == '[')
	{
		/* IP v6 : http://[2a00:1450:8002::6a]/path/abc */
		char * scope;
		scope = strchr(p1, '%');
		p2 = strchr(p1, ']');
		if(p2 && scope && scope < p2 && scope_id) {
			/* parse scope */
#ifdef IF_NAMESIZE
			char tmp[IF_NAMESIZE];
			int l;
			scope++;
			/* "%25" is just '%' in URL encoding */
			if(scope[0] == '2' && scope[1] == '5')
				scope += 2;	/* skip "25" */
			l = (int)(p2 - scope);
			if(l >= IF_NAMESIZE)
				l = IF_NAMESIZE - 1;
			memcpy(tmp, scope, l);
			tmp[l] = '\0';
			*scope_id = if_nametoindex(tmp);
			if(*scope_id == 0) {
				*scope_id = (unsigned int)strtoul(tmp, NULL, 10);
			}
#else
			/* under windows, scope is numerical */
			char tmp[8];
			int l;
			scope++;
			/* "%25" is just '%' in URL encoding */
			if(scope[0] == '2' && scope[1] == '5')
				scope += 2;	/* skip "25" */
			l = p2 - scope;
			if(l >= sizeof(tmp))
				l = sizeof(tmp) - 1;
			memcpy(tmp, scope, l);
			tmp[l] = '\0';
			*scope_id = (unsigned int)strtoul(tmp, NULL, 10);
#endif
		}
		p3 = strchr(p1, '/');
		if(p2 && p3)
		{
			p2++;
			strncpy(hostname, p1, MIN(MAXHOSTNAMELEN, (int)(p2-p1)));
			if(*p2 == ':')
			{
				*port = 0;
				p2++;
				while( (*p2 >= '0') && (*p2 <= '9'))
				{
					*port *= 10;
					*port += (unsigned short)(*p2 - '0');
					p2++;
				}
			}
			else
			{
				*port = 80;
			}
			*path = p3;
			return 1;
		}
	}
	p2 = strchr(p1, ':');
	p3 = strchr(p1, '/');
	if(!p3)
		return 0;
	if(!p2 || (p2>p3))
	{
		strncpy(hostname, p1, MIN(MAXHOSTNAMELEN, (int)(p3-p1)));
		*port = 80;
	}
	else
	{
		strncpy(hostname, p1, MIN(MAXHOSTNAMELEN, (int)(p2-p1)));
		*port = 0;
		p2++;
		while( (*p2 >= '0') && (*p2 <= '9'))
		{
			*port *= 10;
			*port += (unsigned short)(*p2 - '0');
			p2++;
		}
	}
	*path = p3;
	return 1;
}