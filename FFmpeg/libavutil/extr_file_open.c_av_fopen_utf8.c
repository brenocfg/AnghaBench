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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int O_APPEND ; 
 int O_BINARY ; 
 int O_CREAT ; 
 int O_RDONLY ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int avpriv_open (char const*,int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * fdopen (int,char const*) ; 

FILE *av_fopen_utf8(const char *path, const char *mode)
{
    int fd;
    int access;
    const char *m = mode;

    switch (*m++) {
    case 'r': access = O_RDONLY; break;
    case 'w': access = O_CREAT|O_WRONLY|O_TRUNC; break;
    case 'a': access = O_CREAT|O_WRONLY|O_APPEND; break;
    default :
        errno = EINVAL;
        return NULL;
    }
    while (*m) {
        if (*m == '+') {
            access &= ~(O_RDONLY | O_WRONLY);
            access |= O_RDWR;
        } else if (*m == 'b') {
#ifdef O_BINARY
            access |= O_BINARY;
#endif
        } else if (*m) {
            errno = EINVAL;
            return NULL;
        }
        m++;
    }
    fd = avpriv_open(path, access, 0666);
    if (fd == -1)
        return NULL;
    return fdopen(fd, mode);
}