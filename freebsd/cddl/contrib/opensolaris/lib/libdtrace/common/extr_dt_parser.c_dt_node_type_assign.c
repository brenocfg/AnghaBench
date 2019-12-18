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
typedef  scalar_t__ uint_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_6__ {int dn_flags; scalar_t__ dn_type; int /*<<< orphan*/ * dn_ctfp; } ;
typedef  TYPE_1__ dt_node_t ;
typedef  scalar_t__ ctf_id_t ;
typedef  int /*<<< orphan*/  ctf_file_t ;
struct TYPE_7__ {int cte_bits; int cte_format; } ;
typedef  TYPE_2__ ctf_encoding_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_8__ {int /*<<< orphan*/  pcb_hdl; } ;

/* Variables and functions */
 int CTF_INT_SIGNED ; 
 scalar_t__ CTF_K_ARRAY ; 
 scalar_t__ CTF_K_FLOAT ; 
 scalar_t__ CTF_K_FORWARD ; 
 scalar_t__ CTF_K_FUNCTION ; 
 scalar_t__ CTF_K_INTEGER ; 
 scalar_t__ CTF_K_STRUCT ; 
 scalar_t__ CTF_K_UNION ; 
 int /*<<< orphan*/ * DT_DYN_CTFP (int /*<<< orphan*/ ) ; 
 scalar_t__ DT_DYN_TYPE (int /*<<< orphan*/ ) ; 
 int DT_NF_BITFIELD ; 
 int DT_NF_COOKED ; 
 int DT_NF_REF ; 
 int DT_NF_SIGNED ; 
 int DT_NF_USERLAND ; 
 int NBBY ; 
 scalar_t__ ctf_type_encoding (int /*<<< orphan*/ *,scalar_t__,TYPE_2__*) ; 
 scalar_t__ ctf_type_kind (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ctf_type_resolve (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_3__* yypcb ; 

void
dt_node_type_assign(dt_node_t *dnp, ctf_file_t *fp, ctf_id_t type,
    boolean_t user)
{
	ctf_id_t base = ctf_type_resolve(fp, type);
	uint_t kind = ctf_type_kind(fp, base);
	ctf_encoding_t e;

	dnp->dn_flags &=
	    ~(DT_NF_SIGNED | DT_NF_REF | DT_NF_BITFIELD | DT_NF_USERLAND);

	if (kind == CTF_K_INTEGER && ctf_type_encoding(fp, base, &e) == 0) {
		size_t size = e.cte_bits / NBBY;

		if (size > 8 || (e.cte_bits % NBBY) != 0 || (size & (size - 1)))
			dnp->dn_flags |= DT_NF_BITFIELD;

		if (e.cte_format & CTF_INT_SIGNED)
			dnp->dn_flags |= DT_NF_SIGNED;
	}

	if (kind == CTF_K_FLOAT && ctf_type_encoding(fp, base, &e) == 0) {
		if (e.cte_bits / NBBY > sizeof (uint64_t))
			dnp->dn_flags |= DT_NF_REF;
	}

	if (kind == CTF_K_STRUCT || kind == CTF_K_UNION ||
	    kind == CTF_K_FORWARD ||
	    kind == CTF_K_ARRAY || kind == CTF_K_FUNCTION)
		dnp->dn_flags |= DT_NF_REF;
	else if (yypcb != NULL && fp == DT_DYN_CTFP(yypcb->pcb_hdl) &&
	    type == DT_DYN_TYPE(yypcb->pcb_hdl))
		dnp->dn_flags |= DT_NF_REF;

	if (user)
		dnp->dn_flags |= DT_NF_USERLAND;

	dnp->dn_flags |= DT_NF_COOKED;
	dnp->dn_ctfp = fp;
	dnp->dn_type = type;
}