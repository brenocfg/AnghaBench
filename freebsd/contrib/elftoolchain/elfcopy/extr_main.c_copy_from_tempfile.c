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
 scalar_t__ EXDEV ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ elftc_copyfile (int,int) ; 
 scalar_t__ errno ; 
 int open (char const*,int,int) ; 
 scalar_t__ rename (char const*,char const*) ; 
 scalar_t__ unlink (char const*) ; 

__attribute__((used)) static int
copy_from_tempfile(const char *src, const char *dst, int infd, int *outfd,
    int in_place)
{
	int tmpfd;

	/*
	 * First, check if we can use rename().
	 */
	if (in_place == 0) {
		if (rename(src, dst) >= 0) {
			*outfd = infd;
			return (0);
		} else if (errno != EXDEV)
			return (-1);
	
		/*
		 * If the rename() failed due to 'src' and 'dst' residing in
		 * two different file systems, invoke a helper function in
		 * libelftc to do the copy.
		 */

		if (unlink(dst) < 0)
			return (-1);
	}

	if ((tmpfd = open(dst, O_CREAT | O_TRUNC | O_WRONLY, 0755)) < 0)
		return (-1);

	if (elftc_copyfile(infd, tmpfd) < 0)
		return (-1);

	/*
	 * Remove the temporary file from the file system
	 * namespace, and close its file descriptor.
	 */
	if (unlink(src) < 0)
		return (-1);

	(void) close(infd);

	/*
	 * Return the file descriptor for the destination.
	 */
	*outfd = tmpfd;

	return (0);
}