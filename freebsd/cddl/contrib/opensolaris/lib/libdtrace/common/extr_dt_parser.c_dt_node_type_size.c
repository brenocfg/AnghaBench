#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ dtc_ctfmodel; } ;
struct TYPE_8__ {TYPE_1__ dt_conf; } ;
typedef  TYPE_2__ dtrace_hdl_t ;
struct TYPE_9__ {scalar_t__ dn_kind; int dn_flags; int /*<<< orphan*/  dn_type; int /*<<< orphan*/  dn_ctfp; int /*<<< orphan*/ * dn_ident; int /*<<< orphan*/  dn_string; } ;
typedef  TYPE_3__ dt_node_t ;
typedef  int /*<<< orphan*/  ctf_id_t ;
struct TYPE_10__ {TYPE_2__* pcb_hdl; } ;

/* Variables and functions */
 scalar_t__ CTF_K_FORWARD ; 
 scalar_t__ CTF_K_POINTER ; 
 scalar_t__ CTF_MODEL_ILP32 ; 
 scalar_t__ CTF_MODEL_LP64 ; 
 int DT_NF_USERLAND ; 
 scalar_t__ DT_NODE_STRING ; 
 scalar_t__ ctf_getmodel (int /*<<< orphan*/ ) ; 
 scalar_t__ ctf_type_kind (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_type_resolve (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t ctf_type_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t dt_ident_size (int /*<<< orphan*/ *) ; 
 scalar_t__ dt_node_is_dynamic (TYPE_3__ const*) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 
 TYPE_4__* yypcb ; 

size_t
dt_node_type_size(const dt_node_t *dnp)
{
	ctf_id_t base;
	dtrace_hdl_t *dtp = yypcb->pcb_hdl;

	if (dnp->dn_kind == DT_NODE_STRING)
		return (strlen(dnp->dn_string) + 1);

	if (dt_node_is_dynamic(dnp) && dnp->dn_ident != NULL)
		return (dt_ident_size(dnp->dn_ident));

	base = ctf_type_resolve(dnp->dn_ctfp, dnp->dn_type);

	if (ctf_type_kind(dnp->dn_ctfp, base) == CTF_K_FORWARD)
		return (0);

	/*
	 * Here we have a 32-bit user pointer that is being used with a 64-bit
	 * kernel. When we're using it and its tagged as a userland reference --
	 * then we need to keep it as a 32-bit pointer. However, if we are
	 * referring to it as a kernel address, eg. being used after a copyin()
	 * then we need to make sure that we actually return the kernel's size
	 * of a pointer, 8 bytes.
	 */
	if (ctf_type_kind(dnp->dn_ctfp, base) == CTF_K_POINTER &&
	    ctf_getmodel(dnp->dn_ctfp) == CTF_MODEL_ILP32 &&
	    !(dnp->dn_flags & DT_NF_USERLAND) &&
	    dtp->dt_conf.dtc_ctfmodel == CTF_MODEL_LP64)
			return (8);

	return (ctf_type_size(dnp->dn_ctfp, dnp->dn_type));
}