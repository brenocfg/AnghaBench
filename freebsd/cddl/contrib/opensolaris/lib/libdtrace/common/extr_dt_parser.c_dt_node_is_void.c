#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  dn_type; int /*<<< orphan*/ * dn_ctfp; } ;
typedef  TYPE_1__ dt_node_t ;
typedef  int /*<<< orphan*/  ctf_id_t ;
typedef  int /*<<< orphan*/  ctf_file_t ;
typedef  int /*<<< orphan*/  ctf_encoding_t ;

/* Variables and functions */
 scalar_t__ CTF_K_INTEGER ; 
 scalar_t__ IS_VOID (int /*<<< orphan*/ ) ; 
 scalar_t__ ctf_type_encoding (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ctf_type_kind (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_type_resolve (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dt_node_is_dynamic (TYPE_1__ const*) ; 
 scalar_t__ dt_node_is_stack (TYPE_1__ const*) ; 
 scalar_t__ dt_node_is_symaddr (TYPE_1__ const*) ; 
 scalar_t__ dt_node_is_usymaddr (TYPE_1__ const*) ; 

int
dt_node_is_void(const dt_node_t *dnp)
{
	ctf_file_t *fp = dnp->dn_ctfp;
	ctf_encoding_t e;
	ctf_id_t type;

	if (dt_node_is_dynamic(dnp))
		return (0); /* <DYN> is an alias for void but not the same */

	if (dt_node_is_stack(dnp))
		return (0);

	if (dt_node_is_symaddr(dnp) || dt_node_is_usymaddr(dnp))
		return (0);

	type = ctf_type_resolve(fp, dnp->dn_type);

	return (ctf_type_kind(fp, type) == CTF_K_INTEGER &&
	    ctf_type_encoding(fp, type, &e) == 0 && IS_VOID(e));
}