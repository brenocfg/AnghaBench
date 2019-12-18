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
struct UPNParg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*) ; 
 char* simpleUPnPcommand2 (int,char const*,char const*,char const*,struct UPNParg*,int*,char*) ; 

char * simpleUPnPcommand(int s, const char * url, const char * service,
		       const char * action, struct UPNParg * args,
		       int * bufsize)
{
	char * buf;

#if 1
	buf = simpleUPnPcommand2(s, url, service, action, args, bufsize, "1.1");
#else
	buf = simpleUPnPcommand2(s, url, service, action, args, bufsize, "1.0");
	if (!buf || *bufsize == 0)
	{
#if DEBUG
	    printf("Error or no result from SOAP request; retrying with HTTP/1.1\n");
#endif
		buf = simpleUPnPcommand2(s, url, service, action, args, bufsize, "1.1");
	}
#endif
	return buf;
}