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

/* Variables and functions */
 int /*<<< orphan*/  __getpwent_a (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct passwd**) ; 
 scalar_t__ f ; 
 scalar_t__ fopen (char*,char*) ; 
 int /*<<< orphan*/  line ; 
 int /*<<< orphan*/  pw ; 
 int /*<<< orphan*/  size ; 

struct passwd *getpwent()
{
	struct passwd *res;
	if (!f) f = fopen("/etc/passwd", "rbe");
	if (!f) return 0;
	__getpwent_a(f, &pw, &line, &size, &res);
	return res;
}