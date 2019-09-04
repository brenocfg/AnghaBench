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

/* Variables and functions */
 int /*<<< orphan*/  __getgrent_a (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *,size_t*,struct group**) ; 
 scalar_t__ f ; 
 scalar_t__ fopen (char*,char*) ; 
 int /*<<< orphan*/  gr ; 
 int /*<<< orphan*/  line ; 
 int /*<<< orphan*/  mem ; 

struct group *getgrent()
{
	struct group *res;
	size_t size=0, nmem=0;
	if (!f) f = fopen("/etc/group", "rbe");
	if (!f) return 0;
	__getgrent_a(f, &gr, &line, &size, &mem, &nmem, &res);
	return res;
}