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
typedef  int /*<<< orphan*/  buff ;

/* Variables and functions */
 long FDFS_MAX_SERVER_ID ; 
 int FDFS_STORAGE_ID_MAX_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,long) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 long strtol (char const*,char**,int) ; 

bool fdfs_is_server_id_valid(const char *id)
{
	long n;
	char *endptr;
	char buff[FDFS_STORAGE_ID_MAX_SIZE];

	if (*id == '\0')
	{
		return false;
	}

	endptr = NULL;
	n = strtol(id, &endptr, 10);
	if (endptr != NULL && *endptr != '\0')
	{
		return false;
	}

	if (n <= 0 || n > FDFS_MAX_SERVER_ID)
	{
		return false;
	}

	snprintf(buff, sizeof(buff), "%ld", n);
	return strcmp(buff, id) == 0;
}