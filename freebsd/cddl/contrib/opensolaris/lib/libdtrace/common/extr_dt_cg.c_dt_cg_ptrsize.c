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
typedef  scalar_t__ uint_t ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  dt_regset_t ;
struct TYPE_8__ {int /*<<< orphan*/  dn_type; int /*<<< orphan*/ * dn_ctfp; } ;
typedef  TYPE_2__ dt_node_t ;
typedef  int /*<<< orphan*/  dt_irlist_t ;
typedef  int /*<<< orphan*/  dif_instr_t ;
typedef  int /*<<< orphan*/  ctf_id_t ;
typedef  int /*<<< orphan*/  ctf_file_t ;
struct TYPE_9__ {int /*<<< orphan*/  ctr_contents; } ;
typedef  TYPE_3__ ctf_arinfo_t ;
struct TYPE_10__ {int /*<<< orphan*/  pcb_jmpbuf; TYPE_1__* pcb_hdl; } ;
struct TYPE_7__ {int /*<<< orphan*/  dt_ctferr; } ;

/* Variables and functions */
 scalar_t__ CTF_K_ARRAY ; 
 scalar_t__ CTF_K_POINTER ; 
 int /*<<< orphan*/  DIF_INSTR_FMT (scalar_t__,int,int,int) ; 
 int /*<<< orphan*/  DT_LBL_NONE ; 
 int /*<<< orphan*/  EDT_CTF ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ctf_array_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  ctf_errno (int /*<<< orphan*/ *) ; 
 scalar_t__ ctf_type_kind (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_type_reference (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_type_resolve (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ctf_type_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_cg_node_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_cg_setx (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  dt_irlist_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dt_regset_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_regset_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* yypcb ; 

__attribute__((used)) static void
dt_cg_ptrsize(dt_node_t *dnp, dt_irlist_t *dlp, dt_regset_t *drp,
    uint_t op, int dreg)
{
	ctf_file_t *ctfp = dnp->dn_ctfp;
	ctf_arinfo_t r;
	dif_instr_t instr;
	ctf_id_t type;
	uint_t kind;
	ssize_t size;
	int sreg;

	type = ctf_type_resolve(ctfp, dnp->dn_type);
	kind = ctf_type_kind(ctfp, type);
	assert(kind == CTF_K_POINTER || kind == CTF_K_ARRAY);

	if (kind == CTF_K_ARRAY) {
		if (ctf_array_info(ctfp, type, &r) != 0) {
			yypcb->pcb_hdl->dt_ctferr = ctf_errno(ctfp);
			longjmp(yypcb->pcb_jmpbuf, EDT_CTF);
		}
		type = r.ctr_contents;
	} else
		type = ctf_type_reference(ctfp, type);

	if ((size = ctf_type_size(ctfp, type)) == 1)
		return; /* multiply or divide by one can be omitted */

	sreg = dt_regset_alloc(drp);
	dt_cg_setx(dlp, sreg, size);
	instr = DIF_INSTR_FMT(op, dreg, sreg, dreg);
	dt_irlist_append(dlp, dt_cg_node_alloc(DT_LBL_NONE, instr));
	dt_regset_free(drp, sreg);
}