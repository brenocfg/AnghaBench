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
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  execlp (char*,char*,char*,char*,char*,char*,char*) ; 
 int fork () ; 
 int getpid () ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  waitpid (int,int*,int /*<<< orphan*/ ) ; 

int sfs_mksquashfs(char *source, char *destination) {
    pid_t parent = getpid();
    pid_t pid = fork();

    if (pid == -1) {
        // error, failed to fork()
        return(-1);
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
    } else {
        // we are the child
        execlp("mksquashfs", "mksquashfs", source, destination, "-root-owned", "-noappend", (char *)0);
        perror("execlp");   // execvp() returns only on error
        return(-1); // exec never returns
    }
    return(0);
}