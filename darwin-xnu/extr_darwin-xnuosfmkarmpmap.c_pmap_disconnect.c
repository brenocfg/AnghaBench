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
typedef  int /*<<< orphan*/  ppnum_t ;

/* Variables and functions */
 unsigned int pmap_get_refmod (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_page_protect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

unsigned int
pmap_disconnect(
	ppnum_t pn)
{
	pmap_page_protect(pn, 0);	/* disconnect the page */
	return (pmap_get_refmod(pn));	/* return ref/chg status */
}