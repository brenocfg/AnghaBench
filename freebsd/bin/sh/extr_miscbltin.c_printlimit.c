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
struct rlimit {scalar_t__ rlim_max; scalar_t__ rlim_cur; } ;
struct limits {scalar_t__ factor; } ;
typedef  scalar_t__ rlim_t ;
typedef  int /*<<< orphan*/  intmax_t ;
typedef  enum limithow { ____Placeholder_limithow } limithow ;

/* Variables and functions */
 int HARD ; 
 scalar_t__ RLIM_INFINITY ; 
 int SOFT ; 
 int /*<<< orphan*/  out1fmt (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out1str (char*) ; 

__attribute__((used)) static void
printlimit(enum limithow how, const struct rlimit *limit,
    const struct limits *l)
{
	rlim_t val = 0;

	if (how & SOFT)
		val = limit->rlim_cur;
	else if (how & HARD)
		val = limit->rlim_max;
	if (val == RLIM_INFINITY)
		out1str("unlimited\n");
	else
	{
		val /= l->factor;
		out1fmt("%jd\n", (intmax_t)val);
	}
}