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
struct magic_set {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  pat; int /*<<< orphan*/  rx; } ;
typedef  TYPE_1__ file_regex_t ;
typedef  int /*<<< orphan*/  errmsg ;

/* Variables and functions */
 int /*<<< orphan*/  file_magerror (struct magic_set*,char*,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  regerror (int,int /*<<< orphan*/ *,char*,int) ; 

void
file_regerror(file_regex_t *rx, int rc, struct magic_set *ms)
{
	char errmsg[512];

	(void)regerror(rc, &rx->rx, errmsg, sizeof(errmsg));
	file_magerror(ms, "regex error %d for `%s', (%s)", rc, rx->pat,
	    errmsg);
}