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
typedef  int /*<<< orphan*/  upl_t ;
typedef  int /*<<< orphan*/  upl_page_info_t ;

/* Variables and functions */
 int /*<<< orphan*/ * UPL_GET_INTERNAL_PAGE_LIST (int /*<<< orphan*/ ) ; 

upl_page_info_t *
ubc_upl_pageinfo(
	upl_t			upl)
{	       
	return (UPL_GET_INTERNAL_PAGE_LIST(upl));
}