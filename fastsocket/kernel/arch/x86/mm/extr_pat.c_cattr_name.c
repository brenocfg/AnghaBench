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
 unsigned long _PAGE_CACHE_MASK ; 
#define  _PAGE_CACHE_UC 131 
#define  _PAGE_CACHE_UC_MINUS 130 
#define  _PAGE_CACHE_WB 129 
#define  _PAGE_CACHE_WC 128 

__attribute__((used)) static char *cattr_name(unsigned long flags)
{
	switch (flags & _PAGE_CACHE_MASK) {
	case _PAGE_CACHE_UC:		return "uncached";
	case _PAGE_CACHE_UC_MINUS:	return "uncached-minus";
	case _PAGE_CACHE_WB:		return "write-back";
	case _PAGE_CACHE_WC:		return "write-combining";
	default:			return "broken";
	}
}