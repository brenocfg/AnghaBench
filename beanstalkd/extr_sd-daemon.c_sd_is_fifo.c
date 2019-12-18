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
struct stat {scalar_t__ st_dev; scalar_t__ st_ino; int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  st_path ;
typedef  int /*<<< orphan*/  st_fd ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOTDIR ; 
 int /*<<< orphan*/  S_ISFIFO (int /*<<< orphan*/ ) ; 
 int errno ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int /*<<< orphan*/  memset (struct stat*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stat (char const*,struct stat*) ; 

int sd_is_fifo(int fd, const char *path) {
        struct stat st_fd;

        if (fd < 0)
                return -EINVAL;

        memset(&st_fd, 0, sizeof(st_fd));
        if (fstat(fd, &st_fd) < 0)
                return -errno;

        if (!S_ISFIFO(st_fd.st_mode))
                return 0;

        if (path) {
                struct stat st_path;

                memset(&st_path, 0, sizeof(st_path));
                if (stat(path, &st_path) < 0) {

                        if (errno == ENOENT || errno == ENOTDIR)
                                return 0;

                        return -errno;
                }

                return
                        st_path.st_dev == st_fd.st_dev &&
                        st_path.st_ino == st_fd.st_ino;
        }

        return 1;
}