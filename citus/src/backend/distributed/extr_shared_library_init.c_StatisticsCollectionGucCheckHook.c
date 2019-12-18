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
typedef  int /*<<< orphan*/  GucSource ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  GUC_check_errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GUC_check_errdetail (char*) ; 

__attribute__((used)) static bool
StatisticsCollectionGucCheckHook(bool *newval, void **extra, GucSource source)
{
#ifdef HAVE_LIBCURL
	return true;
#else

	/* if libcurl is not installed, only accept false */
	if (*newval)
	{
		GUC_check_errcode(ERRCODE_FEATURE_NOT_SUPPORTED);
		GUC_check_errdetail("Citus was compiled without libcurl support.");
		return false;
	}
	else
	{
		return true;
	}
#endif
}