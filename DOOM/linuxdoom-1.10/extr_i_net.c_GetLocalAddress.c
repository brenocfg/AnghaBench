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
struct hostent {scalar_t__* h_addr_list; } ;
typedef  int /*<<< orphan*/  hostname ;

/* Variables and functions */
 int /*<<< orphan*/  I_Error (char*,...) ; 
 int /*<<< orphan*/  errno ; 
 struct hostent* gethostbyname (char*) ; 
 int gethostname (char*,int) ; 

int GetLocalAddress (void)
{
    char		hostname[1024];
    struct hostent*	hostentry;	// host information entry
    int			v;

    // get local address
    v = gethostname (hostname, sizeof(hostname));
    if (v == -1)
	I_Error ("GetLocalAddress : gethostname: errno %d",errno);
	
    hostentry = gethostbyname (hostname);
    if (!hostentry)
	I_Error ("GetLocalAddress : gethostbyname: couldn't get local host");
		
    return *(int *)hostentry->h_addr_list[0];
}