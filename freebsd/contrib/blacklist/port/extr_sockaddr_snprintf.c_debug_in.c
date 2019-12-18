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
struct TYPE_2__ {int s_addr; } ;
struct sockaddr_in {int sin_family; int sin_port; TYPE_1__ sin_addr; } ;

/* Variables and functions */
 int SLEN (struct sockaddr_in const*) ; 
 int snprintf (char*,size_t,char*,int,int,int,int) ; 

__attribute__((used)) static int
debug_in(char *str, size_t len, const struct sockaddr_in *sin)
{
	return snprintf(str, len, "sin_len=%u, sin_family=%u, sin_port=%u, "
	    "sin_addr.s_addr=%08x",
	    SLEN(sin), sin->sin_family, sin->sin_port,
	    sin->sin_addr.s_addr);
}