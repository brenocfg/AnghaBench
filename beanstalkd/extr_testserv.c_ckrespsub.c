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
 int /*<<< orphan*/  assertf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 char* readline (int) ; 
 int /*<<< orphan*/  strstr (char*,char*) ; 

__attribute__((used)) static void
ckrespsub(int fd, char *sub)
{
    char *line = readline(fd);
    assertf(strstr(line, sub), "\"%s\" not in \"%s\"", sub, line);
}