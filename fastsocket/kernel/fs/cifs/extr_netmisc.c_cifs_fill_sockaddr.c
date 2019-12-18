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
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cifs_convert_address (struct sockaddr*,char const*,int) ; 
 int cifs_set_port (struct sockaddr*,unsigned short const) ; 

int
cifs_fill_sockaddr(struct sockaddr *dst, const char *src, int len,
		   const unsigned short int port)
{
	if (!cifs_convert_address(dst, src, len))
		return 0;
	return cifs_set_port(dst, port);
}