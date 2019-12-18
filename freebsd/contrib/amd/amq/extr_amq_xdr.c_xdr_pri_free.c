#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ caddr_t ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  (* XDRPROC_T_TYPE ) (TYPE_1__*,scalar_t__*) ;
struct TYPE_5__ {int /*<<< orphan*/  x_op; } ;
typedef  TYPE_1__ XDR ;

/* Variables and functions */
 int /*<<< orphan*/  XDR_FREE ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,scalar_t__*) ; 

bool_t
xdr_pri_free(XDRPROC_T_TYPE xdr_args, caddr_t args_ptr)
{
  XDR xdr;

  xdr.x_op = XDR_FREE;
  return ((*xdr_args) (&xdr, (caddr_t *) args_ptr));
}