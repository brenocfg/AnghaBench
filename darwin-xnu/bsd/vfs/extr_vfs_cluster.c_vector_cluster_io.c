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
typedef  int /*<<< orphan*/  vnode_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  upl_t ;
struct clios {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  buf_t ;

/* Variables and functions */
 int CL_PRESERVE ; 
 int CL_READ ; 
 int PAGE_MASK ; 
 int cluster_io (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,struct clios*,int (*) (int /*<<< orphan*/ ,void*),void*) ; 
 int /*<<< orphan*/  vector_upl_set_pagelist (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vector_cluster_io(vnode_t vp, upl_t vector_upl, vm_offset_t vector_upl_offset, off_t v_upl_uio_offset, int vector_upl_iosize,
	   int io_flag, buf_t real_bp, struct clios *iostate, int (*callback)(buf_t, void *), void *callback_arg)
{
	vector_upl_set_pagelist(vector_upl);

	if(io_flag & CL_READ) {	
		if(vector_upl_offset == 0 && ((vector_upl_iosize & PAGE_MASK)==0))
       			io_flag &= ~CL_PRESERVE; /*don't zero fill*/
		else
       			io_flag |= CL_PRESERVE; /*zero fill*/
	}	
	return (cluster_io(vp, vector_upl, vector_upl_offset, v_upl_uio_offset, vector_upl_iosize, io_flag, real_bp, iostate, callback, callback_arg));

}