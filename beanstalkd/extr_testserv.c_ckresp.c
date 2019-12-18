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
 int /*<<< orphan*/  assertf (int,char*,char*,char*) ; 
 char* readline (int) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void
ckresp(int fd, char *exp)
{
    char *line = readline(fd);
    assertf(strcmp(exp, line) == 0, "\"%s\" != \"%s\"", exp, line);
}