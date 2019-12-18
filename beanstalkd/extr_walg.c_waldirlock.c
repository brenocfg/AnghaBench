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
struct flock {scalar_t__ l_len; scalar_t__ l_start; int /*<<< orphan*/  l_whence; int /*<<< orphan*/  l_type; } ;
struct TYPE_3__ {char* dir; } ;
typedef  TYPE_1__ Wal ;

/* Variables and functions */
 int /*<<< orphan*/  F_SETLK ; 
 int /*<<< orphan*/  F_WRLCK ; 
 int O_CREAT ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int fcntl (int,int /*<<< orphan*/ ,struct flock*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  twarn (char*) ; 

int
waldirlock(Wal *w)
{
    int r;
    int fd;
    struct flock lk;
    char *path;
    size_t path_length;

    path_length = strlen(w->dir) + strlen("/lock") + 1;
    if ((path = malloc(path_length)) == NULL) {
        twarn("malloc");
        return 0;
    }
    snprintf(path, path_length, "%s/lock", w->dir);

    fd = open(path, O_WRONLY|O_CREAT, 0600);
    free(path);
    if (fd == -1) {
        twarn("open");
        return 0;
    }

    lk.l_type = F_WRLCK;
    lk.l_whence = SEEK_SET;
    lk.l_start = 0;
    lk.l_len = 0;
    r = fcntl(fd, F_SETLK, &lk);
    if (r) {
        twarn("fcntl");
        return 0;
    }

    // intentionally leak fd, since we never want to close it
    // and we'll never need it again
    return 1;
}