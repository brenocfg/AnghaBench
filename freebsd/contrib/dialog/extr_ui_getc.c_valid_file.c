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
 int FALSE ; 
 int /*<<< orphan*/  F_GETFL ; 
 int TRUE ; 
 scalar_t__ fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fileno (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
valid_file(FILE *fp)
{
    bool code = FALSE;
    int fd = fileno(fp);

    if (fd >= 0) {
	if (fcntl(fd, F_GETFL, 0) >= 0) {
	    code = TRUE;
	}
    }
    return code;
}