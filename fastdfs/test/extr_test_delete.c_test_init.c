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
 int EPERM ; 
 char* FILENAME_FAIL ; 
 char* STRERROR (int) ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ chdir (char*) ; 
 int errno ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/ * fpFail ; 
 scalar_t__ mkdir (char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int proccess_index ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int) ; 

__attribute__((used)) static int test_init()
{
	char filename[64];

	if (access("delete", 0) != 0 && mkdir("delete", 0755) != 0)
	{
	}

	if (chdir("delete") != 0)
	{
		printf("chdir fail, errno: %d, error info: %s\n", errno, STRERROR(errno));
		return errno != 0 ? errno : EPERM;
	}

	sprintf(filename, "%s.%d", FILENAME_FAIL, proccess_index);
	if ((fpFail=fopen(filename, "wb")) == NULL)
	{
		printf("open file %s fail, errno: %d, error info: %s\n", 
			filename, errno, STRERROR(errno));
		return errno != 0 ? errno : EPERM;
	}

	return 0;
}