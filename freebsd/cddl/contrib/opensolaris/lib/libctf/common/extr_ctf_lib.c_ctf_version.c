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
 int CTF_VERSION ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOTSUP ; 
 int _libctf_version ; 
 int /*<<< orphan*/  ctf_dprintf (char*,int) ; 
 int /*<<< orphan*/  errno ; 

int
ctf_version(int version)
{
	if (version < 0) {
		errno = EINVAL;
		return (-1);
	}

	if (version > 0) {
		if (version > CTF_VERSION) {
			errno = ENOTSUP;
			return (-1);
		}
		ctf_dprintf("ctf_version: client using version %d\n", version);
		_libctf_version = version;
	}

	return (_libctf_version);
}