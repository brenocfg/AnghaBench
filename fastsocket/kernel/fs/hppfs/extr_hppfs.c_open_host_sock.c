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
 int os_connect_socket (char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static int open_host_sock(char *host_file, int *filter_out)
{
	char *end;
	int fd;

	end = &host_file[strlen(host_file)];
	strcpy(end, "/rw");
	*filter_out = 1;
	fd = os_connect_socket(host_file);
	if (fd > 0)
		return fd;

	strcpy(end, "/r");
	*filter_out = 0;
	fd = os_connect_socket(host_file);
	return fd;
}