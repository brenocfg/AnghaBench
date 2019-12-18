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
 char* FILENAME_FILE_ID ; 
 char* STRERROR (int) ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ chdir (char*) ; 
 int errno ; 
 void* fopen (char*,char*) ; 
 int /*<<< orphan*/ * fpFail ; 
 int /*<<< orphan*/ * fpSuccess ; 
 scalar_t__ mkdir (char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int proccess_index ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int) ; 

__attribute__((used)) static int test_init()
{
	char filename[64];

	if (access("upload", 0) != 0 && mkdir("upload", 0755) != 0)
	{
	}

	if (chdir("upload") != 0)
	{
		printf("chdir fail, errno: %d, error info: %s\n", errno, STRERROR(errno));
		return errno != 0 ? errno : EPERM;
	}

	sprintf(filename, "%s.%d", FILENAME_FILE_ID, proccess_index);
	if ((fpSuccess=fopen(filename, "wb")) == NULL)
	{
		printf("open file %s fail, errno: %d, error info: %s\n", 
			filename, errno, STRERROR(errno));
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