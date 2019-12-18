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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  PBI_BB_WriteConfig (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PBI_MIO_WriteConfig (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PBI_PROTO80_WriteConfig (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PBI_XLD_WriteConfig (int /*<<< orphan*/ *) ; 

void PBI_WriteConfig(FILE *fp)
{
#ifdef PBI_MIO
	PBI_MIO_WriteConfig(fp);
#endif
#ifdef PBI_BB
	PBI_BB_WriteConfig(fp);
#endif
#ifdef PBI_XLD
	PBI_XLD_WriteConfig(fp);
#endif
#ifdef PBI_PROTO80
	PBI_PROTO80_WriteConfig(fp);
#endif
}