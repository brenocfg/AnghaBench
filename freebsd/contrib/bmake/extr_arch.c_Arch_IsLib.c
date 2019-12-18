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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  armag ;
struct TYPE_3__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ GNode ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ memcmp (char*,char const*,int) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int read (int,char*,int) ; 

int
Arch_IsLib(GNode *gn)
{
    static const char armag[] = "!<arch>\n";
    char buf[sizeof(armag)-1];
    int fd;

    if ((fd = open(gn->path, O_RDONLY)) == -1)
	return FALSE;

    if (read(fd, buf, sizeof(buf)) != sizeof(buf)) {
	(void)close(fd);
	return FALSE;
    }

    (void)close(fd);

    return memcmp(buf, armag, sizeof(buf)) == 0;
}