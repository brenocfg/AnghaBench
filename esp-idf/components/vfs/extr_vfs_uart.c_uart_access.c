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
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  ENOENT ; 
 int F_OK ; 
 int R_OK ; 
 int W_OK ; 
 int X_OK ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int uart_access(const char *path, int amode)
{
    int ret = -1;

    if (strcmp(path, "/0") == 0 || strcmp(path, "/1") == 0 || strcmp(path, "/2") == 0) {
        if (F_OK == amode) {
            ret = 0; //path exists
        } else {
            if ((((amode & R_OK) == R_OK) || ((amode & W_OK) == W_OK)) && ((amode & X_OK) != X_OK)) {
                ret = 0; //path is readable and/or writable but not executable
            } else {
                errno = EACCES;
            }
        }
    } else {
        errno = ENOENT;
    }

    return ret;
}