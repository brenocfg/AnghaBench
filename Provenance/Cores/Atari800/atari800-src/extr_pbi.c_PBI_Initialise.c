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

/* Variables and functions */
 scalar_t__ PBI_BB_Initialise (int*,char**) ; 
 scalar_t__ PBI_MIO_Initialise (int*,char**) ; 
 scalar_t__ PBI_PROTO80_Initialise (int*,char**) ; 
 scalar_t__ PBI_XLD_Initialise (int*,char**) ; 
 scalar_t__ TRUE ; 

int PBI_Initialise(int *argc, char *argv[])
{
	return TRUE
#ifdef PBI_XLD
		&& PBI_XLD_Initialise(argc, argv)
#endif
#ifdef PBI_BB
		&& PBI_BB_Initialise(argc, argv)
#endif
#ifdef PBI_MIO
		&& PBI_MIO_Initialise(argc, argv)
#endif
#ifdef PBI_PROTO80
		&& PBI_PROTO80_Initialise(argc, argv)
#endif
	;
}