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
struct passwd {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  __getpwent_a (int /*<<< orphan*/ *,struct passwd*,char**,size_t*,struct passwd**) ; 

struct passwd *fgetpwent(FILE *f)
{
	static char *line;
	static struct passwd pw;
	size_t size=0;
	struct passwd *res;
	__getpwent_a(f, &pw, &line, &size, &res);
	return res;
}