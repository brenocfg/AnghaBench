#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint_t ;
struct TYPE_5__ {int dn_flags; int /*<<< orphan*/ * dn_ctfp; int /*<<< orphan*/  dn_type; } ;
typedef  TYPE_1__ dt_node_t ;
typedef  int /*<<< orphan*/  ctf_id_t ;
typedef  int /*<<< orphan*/  ctf_file_t ;
struct TYPE_6__ {scalar_t__ cte_format; } ;
typedef  TYPE_2__ ctf_encoding_t ;

/* Variables and functions */
 scalar_t__ CTF_FP_DOUBLE ; 
 scalar_t__ CTF_FP_LDOUBLE ; 
 scalar_t__ CTF_FP_SINGLE ; 
 scalar_t__ CTF_K_FLOAT ; 
 int DT_NF_COOKED ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ctf_type_encoding (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ ctf_type_kind (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_type_resolve (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
dt_node_is_float(const dt_node_t *dnp)
{
	ctf_file_t *fp = dnp->dn_ctfp;
	ctf_encoding_t e;
	ctf_id_t type;
	uint_t kind;

	assert(dnp->dn_flags & DT_NF_COOKED);

	type = ctf_type_resolve(fp, dnp->dn_type);
	kind = ctf_type_kind(fp, type);

	return (kind == CTF_K_FLOAT &&
	    ctf_type_encoding(dnp->dn_ctfp, type, &e) == 0 && (
	    e.cte_format == CTF_FP_SINGLE || e.cte_format == CTF_FP_DOUBLE ||
	    e.cte_format == CTF_FP_LDOUBLE));
}