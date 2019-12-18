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
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,char*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  writefull (int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mustsend(int fd, char *s)
{
    writefull(fd, s, strlen(s));
    printf(">%d %s", fd, s);
    fflush(stdout);
}