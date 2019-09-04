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
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  size_t UINT ;

/* Variables and functions */
 scalar_t__ IsEmptyStr (char*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCpy (char*,size_t,char*) ; 
 int StrLen (char*) ; 
 int stat (char*,struct stat*) ; 

bool ParseUnixEthDeviceName(char *dst_devname, UINT dst_devname_size, char *src_name)
{
	UINT len, i;
	struct stat s;
	int err;
	char *device_path;
	int device_pathlen;

	// Validate arguments
	if (dst_devname == NULL || src_name == NULL)
	{
		return false;
	}

	// Check string length
	if (IsEmptyStr(src_name))
	{
		return false;
	}

	// Solaris 10 and higher make real and virtual devices available in /dev/net
	err = stat("/dev/net", &s);
	if (err != -1 && S_ISDIR(s.st_mode))
	{
		device_path = "/dev/net/";
	}
	else
	{
		device_path = "/dev/";
	}

	device_pathlen = StrLen(device_path);

	// Last character must be a number
	if (src_name[i] < '0' || '9' < src_name[i])
	{
		if (src_name[i + 1] == 0)
		{
			return false;
		}
	}

	StrCpy(dst_devname, dst_devname_size, device_path);
	StrCpy(dst_devname + device_pathlen, dst_devname_size - device_pathlen, src_name);
	dst_devname[device_pathlen + len] = 0;

	return true;
}