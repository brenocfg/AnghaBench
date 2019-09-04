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
typedef  int /*<<< orphan*/  uid_t ;
struct passwd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __getpw_a (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct passwd**) ; 
 int /*<<< orphan*/  line ; 
 int /*<<< orphan*/  pw ; 
 int /*<<< orphan*/  size ; 

struct passwd *getpwuid(uid_t uid)
{
	struct passwd *res;
	__getpw_a(0, uid, &pw, &line, &size, &res);
	return res;
}