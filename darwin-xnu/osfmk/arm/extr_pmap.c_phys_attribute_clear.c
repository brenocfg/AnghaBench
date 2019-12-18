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
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int PMAP_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_TRACE (int,int,...) ; 
 int /*<<< orphan*/  PMAP__ATTRIBUTE_CLEAR ; 
 int /*<<< orphan*/  phys_attribute_clear_internal (int /*<<< orphan*/ ,unsigned int,int,void*) ; 

__attribute__((used)) static void
phys_attribute_clear(
	ppnum_t		pn,
	unsigned int	bits,
	int		options,
	void		*arg)
{
	/*
	 * Do we really want this tracepoint?  It will be extremely chatty.
	 * Also, should we have a corresponding trace point for the set path?
	 */
	PMAP_TRACE(3, PMAP_CODE(PMAP__ATTRIBUTE_CLEAR) | DBG_FUNC_START, pn, bits);

	phys_attribute_clear_internal(pn, bits, options, arg);

	PMAP_TRACE(3, PMAP_CODE(PMAP__ATTRIBUTE_CLEAR) | DBG_FUNC_END);
}