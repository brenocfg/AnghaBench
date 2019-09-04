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
typedef  int /*<<< orphan*/  template ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int ENOENT ; 
 char* calloc (scalar_t__,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int createTmpfileCloexec (char*) ; 
 int errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 int posix_fallocate (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

int
createAnonymousFile(off_t size)
{
    static const char template[] = "/glfw-shared-XXXXXX";
    const char* path;
    char* name;
    int fd;
    int ret;

    path = getenv("XDG_RUNTIME_DIR");
    if (!path)
    {
        errno = ENOENT;
        return -1;
    }

    name = calloc(strlen(path) + sizeof(template), 1);
    strcpy(name, path);
    strcat(name, template);

    fd = createTmpfileCloexec(name);

    free(name);

    if (fd < 0)
        return -1;
    ret = posix_fallocate(fd, 0, size);
    if (ret != 0)
    {
        close(fd);
        errno = ret;
        return -1;
    }
    return fd;
}