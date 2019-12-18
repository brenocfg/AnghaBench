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
typedef  scalar_t__ uint_t ;
struct TYPE_3__ {int dn_flags; int /*<<< orphan*/  dn_type; int /*<<< orphan*/ * dn_ctfp; } ;
typedef  TYPE_1__ dt_node_t ;
typedef  int /*<<< orphan*/  ctf_id_t ;
typedef  int /*<<< orphan*/  ctf_file_t ;
typedef  int /*<<< orphan*/  ctf_encoding_t ;

/* Variables and functions */
 scalar_t__ CTF_K_FUNCTION ; 
 scalar_t__ CTF_K_INTEGER ; 
 scalar_t__ CTF_K_POINTER ; 
 int DT_NF_COOKED ; 
 scalar_t__ IS_VOID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ctf_type_encoding (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ctf_type_kind (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_type_reference (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_type_resolve (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
dt_node_is_vfptr(const dt_node_t *dnp)
{
	ctf_file_t *fp = dnp->dn_ctfp;
	ctf_encoding_t e;
	ctf_id_t type;
	uint_t kind;

	assert(dnp->dn_flags & DT_NF_COOKED);

	type = ctf_type_resolve(fp, dnp->dn_type);
	if (ctf_type_kind(fp, type) != CTF_K_POINTER)
		return (0); /* type is not a pointer */

	type = ctf_type_resolve(fp, ctf_type_reference(fp, type));
	kind = ctf_type_kind(fp, type);

	return (kind == CTF_K_FUNCTION || (kind == CTF_K_INTEGER &&
	    ctf_type_encoding(fp, type, &e) == 0 && IS_VOID(e)));
}