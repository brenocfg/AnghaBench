#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ tv_sec; scalar_t__ tv_nsec; } ;
struct stat {TYPE_1__ st_mtim; } ;

/* Variables and functions */
 scalar_t__ stat (char const*,struct stat*) ; 

__attribute__((used)) static int
newerf (const char *f1, const char *f2)
{
	struct stat b1, b2;

	if (stat(f1, &b1) != 0 || stat(f2, &b2) != 0)
		return 0;

	if (b1.st_mtim.tv_sec > b2.st_mtim.tv_sec)
		return 1;
	if (b1.st_mtim.tv_sec < b2.st_mtim.tv_sec)
		return 0;

       return (b1.st_mtim.tv_nsec > b2.st_mtim.tv_nsec);
}