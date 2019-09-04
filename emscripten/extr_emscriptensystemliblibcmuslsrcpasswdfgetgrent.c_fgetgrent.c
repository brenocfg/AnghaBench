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
struct group {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  __getgrent_a (int /*<<< orphan*/ *,struct group*,char**,size_t*,char***,size_t*,struct group**) ; 

struct group *fgetgrent(FILE *f)
{
	static char *line, **mem;
	static struct group gr;
	struct group *res;
	size_t size=0, nmem=0;
	__getgrent_a(f, &gr, &line, &size, &mem, &nmem, &res);
	return res;
}