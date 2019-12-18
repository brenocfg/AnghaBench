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
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSPC ; 
 int /*<<< orphan*/  O_WRONLY ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  dup2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  execvp (char*,char**) ; 
 scalar_t__ fork () ; 
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  open (char*,int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char const*,size_t) ; 
 scalar_t__ waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 

int shell_cmd(const char *substs[][2], const char *args_str, int silent)
{
    char * args[64];
    char   cmdbuf[4096];
    pid_t  child;
    size_t args_i = 0, cmdbuf_i = 0, args_str_i, i;
    int    c, exit_status, is_space = 1;

    errno = ENOSPC;
    for (args_str_i = 0; (c = args_str[args_str_i]) != 0; args_str_i++) {
        if (isspace((unsigned char) c)) {
            if (!is_space) {
                if (cmdbuf_i >= sizeof cmdbuf) {
                    return -1;
                }
                cmdbuf[cmdbuf_i++] = 0;
            }
            is_space = 1;
            continue;
        }
        if (is_space) {
            if (args_i >= sizeof args / sizeof args[0]) {
                return -1;
            }
            args[args_i++] = &cmdbuf[cmdbuf_i];
        }
        is_space = 0;
        for (i = 0; substs[i][0] != NULL; i++) {
            size_t pat_len = strlen(substs[i][0]), sub_len;
            if (!strncmp(substs[i][0], &args_str[args_str_i], pat_len)) {
                sub_len = strlen(substs[i][1]);
                if (sizeof cmdbuf - cmdbuf_i <= sub_len) {
                    return -1;
                }
                memcpy(&cmdbuf[cmdbuf_i], substs[i][1], sub_len);
                args_str_i += pat_len - 1;
                cmdbuf_i += sub_len;
                break;
            }
        }
        if (substs[i][0] == NULL) {
            if (cmdbuf_i >= sizeof cmdbuf) {
                return -1;
            }
            cmdbuf[cmdbuf_i++] = c;
        }
    }
    if (!is_space) {
        if (cmdbuf_i >= sizeof cmdbuf) {
            return -1;
        }
        cmdbuf[cmdbuf_i++] = 0;
    }
    if (args_i >= sizeof args / sizeof args[0]) {
        return -1;
    }
    args[args_i] = NULL;
    if ((child = fork()) == (pid_t) -1) {
        return -1;
    } else if (child == (pid_t) 0) {
        if (silent) {
            dup2(dup2(open("/dev/null", O_WRONLY), 2), 1);
        }
        execvp(args[0], args);
        _exit(1);
    } else if (waitpid(child, &exit_status, 0) == (pid_t) -1 || !WIFEXITED(exit_status)) {
        return -1;
    }
    return 0;
}