#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_3__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  fd; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ IO ;

/* Variables and functions */
 int D_DISK ; 
 int D_MEM ; 
 int D_TAPE ; 
 scalar_t__ ESPIPE ; 
 int /*<<< orphan*/  FIODTYPE ; 
 int /*<<< orphan*/  ISCHR ; 
 int /*<<< orphan*/  ISPIPE ; 
 int /*<<< orphan*/  ISSEEK ; 
 int /*<<< orphan*/  ISTAPE ; 
 int /*<<< orphan*/  ISTRUNC ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
getfdtype(IO *io)
{
	struct stat sb;
	int type;

	if (fstat(io->fd, &sb) == -1)
		err(1, "%s", io->name);
	if (S_ISREG(sb.st_mode))
		io->flags |= ISTRUNC;
	if (S_ISCHR(sb.st_mode) || S_ISBLK(sb.st_mode)) { 
		if (ioctl(io->fd, FIODTYPE, &type) == -1) {
			err(1, "%s", io->name);
		} else {
			if (type & D_TAPE)
				io->flags |= ISTAPE;
			else if (type & (D_DISK | D_MEM))
				io->flags |= ISSEEK;
			if (S_ISCHR(sb.st_mode) && (type & D_TAPE) == 0)
				io->flags |= ISCHR;
		}
		return;
	}
	errno = 0;
	if (lseek(io->fd, (off_t)0, SEEK_CUR) == -1 && errno == ESPIPE)
		io->flags |= ISPIPE;
	else
		io->flags |= ISSEEK;
}