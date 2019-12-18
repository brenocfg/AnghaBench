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
struct statfs {int f_blocks; int f_bsize; int f_bavail; } ;
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  prthumanval (char*,int) ; 

__attribute__((used)) static void
prthuman(const struct statfs *sfsp, int64_t used)
{

	prthumanval("  {:blocks/%6s}", sfsp->f_blocks * sfsp->f_bsize);
	prthumanval("  {:used/%6s}", used * sfsp->f_bsize);
	prthumanval("  {:available/%6s}", sfsp->f_bavail * sfsp->f_bsize);
}