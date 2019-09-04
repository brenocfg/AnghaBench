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
struct secasvar {int flags; } ;

/* Variables and functions */
 int SADB_X_EXT_OLD ; 

__attribute__((used)) static int
ah_sumsiz_1216(struct secasvar *sav)
{
	if (!sav)
		return -1;
	if (sav->flags & SADB_X_EXT_OLD)
		return 16;
	else
		return 12;
}