#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ dbu_buf; scalar_t__ dbu_ptr; } ;
typedef  TYPE_1__ dt_buf_t ;

/* Variables and functions */
 size_t roundup (size_t,size_t) ; 

size_t
dt_buf_offset(const dt_buf_t *bp, size_t align)
{
	size_t off = (size_t)(bp->dbu_ptr - bp->dbu_buf);
	return (roundup(off, align));
}