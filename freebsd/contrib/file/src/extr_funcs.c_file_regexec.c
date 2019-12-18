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
typedef  int /*<<< orphan*/  regmatch_t ;
struct TYPE_3__ {scalar_t__ rc; int /*<<< orphan*/  rx; } ;
typedef  TYPE_1__ file_regex_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int regexec (int /*<<< orphan*/ *,char const*,size_t,int /*<<< orphan*/ *,int) ; 

int
file_regexec(file_regex_t *rx, const char *str, size_t nmatch,
    regmatch_t* pmatch, int eflags)
{
	assert(rx->rc == 0);
	/* XXX: force initialization because glibc does not always do this */
	memset(pmatch, 0, nmatch * sizeof(*pmatch));
	return regexec(&rx->rx, str, nmatch, pmatch, eflags);
}