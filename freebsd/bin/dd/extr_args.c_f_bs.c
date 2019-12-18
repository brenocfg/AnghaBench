#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uintmax_t ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {size_t dbsz; } ;
struct TYPE_3__ {size_t dbsz; } ;

/* Variables and functions */
 int SSIZE_MAX ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ) ; 
 int get_num (char*) ; 
 TYPE_2__ in ; 
 TYPE_1__ out ; 

__attribute__((used)) static void
f_bs(char *arg)
{
	uintmax_t res;

	res = get_num(arg);
	if (res < 1 || res > SSIZE_MAX)
		errx(1, "bs must be between 1 and %zd", (ssize_t)SSIZE_MAX);
	in.dbsz = out.dbsz = (size_t)res;
}