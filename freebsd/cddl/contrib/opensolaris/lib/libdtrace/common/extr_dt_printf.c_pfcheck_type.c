#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dt_pfargv_t ;
struct TYPE_7__ {TYPE_1__* pfd_conv; } ;
typedef  TYPE_2__ dt_pfargd_t ;
struct TYPE_8__ {int /*<<< orphan*/  dn_type; int /*<<< orphan*/  dn_ctfp; } ;
typedef  TYPE_3__ dt_node_t ;
struct TYPE_6__ {int /*<<< orphan*/  pfc_dtype; int /*<<< orphan*/  pfc_dctfp; } ;

/* Variables and functions */
 int ctf_type_compat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_type_resolve (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pfcheck_type(dt_pfargv_t *pfv, dt_pfargd_t *pfd, dt_node_t *dnp)
{
	return (ctf_type_compat(dnp->dn_ctfp, ctf_type_resolve(dnp->dn_ctfp,
	    dnp->dn_type), pfd->pfd_conv->pfc_dctfp, pfd->pfd_conv->pfc_dtype));
}