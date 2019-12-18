#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uchar_t ;
typedef  scalar_t__ ssize_t ;
struct TYPE_4__ {scalar_t__ ctf_size; int /*<<< orphan*/ * ctf_base; } ;
typedef  TYPE_1__ ctf_file_t ;

/* Variables and functions */
 int ctf_set_errno (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ write (int,int /*<<< orphan*/  const*,scalar_t__) ; 

int
ctf_write(ctf_file_t *fp, int fd)
{
	const uchar_t *buf = fp->ctf_base;
	ssize_t resid = fp->ctf_size;
	ssize_t len;

	while (resid != 0) {
		if ((len = write(fd, buf, resid)) <= 0)
			return (ctf_set_errno(fp, errno));
		resid -= len;
		buf += len;
	}

	return (0);
}