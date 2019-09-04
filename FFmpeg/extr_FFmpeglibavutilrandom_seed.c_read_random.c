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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */

__attribute__((used)) static int read_random(uint32_t *dst, const char *file)
{
#if HAVE_UNISTD_H
    int fd = avpriv_open(file, O_RDONLY);
    int err = -1;

    if (fd == -1)
        return -1;
    err = read(fd, dst, sizeof(*dst));
    close(fd);

    return err;
#else
    return -1;
#endif
}