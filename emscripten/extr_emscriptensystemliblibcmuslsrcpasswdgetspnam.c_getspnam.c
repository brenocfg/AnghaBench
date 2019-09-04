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
struct spwd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINE_LIM ; 
 int errno ; 
 int getspnam_r (char const*,struct spwd*,char*,int /*<<< orphan*/ ,struct spwd**) ; 
 char* malloc (int /*<<< orphan*/ ) ; 

struct spwd *getspnam(const char *name)
{
	static struct spwd sp;
	static char *line;
	struct spwd *res;
	int e;

	if (!line) line = malloc(LINE_LIM);
	if (!line) return 0;
	e = getspnam_r(name, &sp, line, LINE_LIM, &res);
	if (e) errno = e;
	return res;
}