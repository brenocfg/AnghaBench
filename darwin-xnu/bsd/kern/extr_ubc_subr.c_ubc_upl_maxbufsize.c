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
typedef  int /*<<< orphan*/  upl_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_UPL_SIZE_BYTES ; 

upl_size_t 
ubc_upl_maxbufsize(
	void)
{
	return(MAX_UPL_SIZE_BYTES);
}