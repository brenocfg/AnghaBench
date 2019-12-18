#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint_t ;
typedef  int ssize_t ;
struct TYPE_11__ {int /*<<< orphan*/  ctt_name; } ;
typedef  TYPE_1__ ctf_type_t ;
typedef  int /*<<< orphan*/  ctf_id_t ;
typedef  int /*<<< orphan*/  ctf_file_t ;
struct TYPE_12__ {scalar_t__ cd_err; size_t* cd_order; size_t cd_len; TYPE_3__* cd_nodes; } ;
typedef  TYPE_2__ ctf_decl_t ;
typedef  size_t ctf_decl_prec_t ;
struct TYPE_13__ {int cd_kind; int /*<<< orphan*/  cd_n; int /*<<< orphan*/  cd_type; } ;
typedef  TYPE_3__ ctf_decl_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTF_ERR ; 
#define  CTF_K_ARRAY 140 
#define  CTF_K_CONST 139 
#define  CTF_K_ENUM 138 
#define  CTF_K_FLOAT 137 
#define  CTF_K_FORWARD 136 
#define  CTF_K_FUNCTION 135 
#define  CTF_K_INTEGER 134 
#define  CTF_K_POINTER 133 
#define  CTF_K_RESTRICT 132 
#define  CTF_K_STRUCT 131 
#define  CTF_K_TYPEDEF 130 
#define  CTF_K_UNION 129 
#define  CTF_K_VOLATILE 128 
 size_t CTF_PREC_ARRAY ; 
 size_t CTF_PREC_BASE ; 
 size_t CTF_PREC_MAX ; 
 size_t CTF_PREC_POINTER ; 
 scalar_t__ ECTF_NAMELEN ; 
 int /*<<< orphan*/  ctf_decl_fini (TYPE_2__*) ; 
 int /*<<< orphan*/  ctf_decl_init (TYPE_2__*,char*,size_t) ; 
 int /*<<< orphan*/  ctf_decl_push (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_decl_sprintf (TYPE_2__*,char*,...) ; 
 TYPE_3__* ctf_list_next (TYPE_3__*) ; 
 TYPE_1__* ctf_lookup_by_id (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int ctf_set_errno (int /*<<< orphan*/ *,scalar_t__) ; 
 char* ctf_strptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
ctf_type_qlname(ctf_file_t *fp, ctf_id_t type, char *buf, size_t len,
    const char *qname)
{
	ctf_decl_t cd;
	ctf_decl_node_t *cdp;
	ctf_decl_prec_t prec, lp, rp;
	int ptr, arr;
	uint_t k;

	if (fp == NULL && type == CTF_ERR)
		return (-1); /* simplify caller code by permitting CTF_ERR */

	ctf_decl_init(&cd, buf, len);
	ctf_decl_push(&cd, fp, type);

	if (cd.cd_err != 0) {
		ctf_decl_fini(&cd);
		return (ctf_set_errno(fp, cd.cd_err));
	}

	/*
	 * If the type graph's order conflicts with lexical precedence order
	 * for pointers or arrays, then we need to surround the declarations at
	 * the corresponding lexical precedence with parentheses.  This can
	 * result in either a parenthesized pointer (*) as in int (*)() or
	 * int (*)[], or in a parenthesized pointer and array as in int (*[])().
	 */
	ptr = cd.cd_order[CTF_PREC_POINTER] > CTF_PREC_POINTER;
	arr = cd.cd_order[CTF_PREC_ARRAY] > CTF_PREC_ARRAY;

	rp = arr ? CTF_PREC_ARRAY : ptr ? CTF_PREC_POINTER : -1;
	lp = ptr ? CTF_PREC_POINTER : arr ? CTF_PREC_ARRAY : -1;

	k = CTF_K_POINTER; /* avoid leading whitespace (see below) */

	for (prec = CTF_PREC_BASE; prec < CTF_PREC_MAX; prec++) {
		for (cdp = ctf_list_next(&cd.cd_nodes[prec]);
		    cdp != NULL; cdp = ctf_list_next(cdp)) {

			ctf_file_t *rfp = fp;
			const ctf_type_t *tp =
			    ctf_lookup_by_id(&rfp, cdp->cd_type);
			const char *name = ctf_strptr(rfp, tp->ctt_name);

			if (k != CTF_K_POINTER && k != CTF_K_ARRAY)
				ctf_decl_sprintf(&cd, " ");

			if (lp == prec) {
				ctf_decl_sprintf(&cd, "(");
				lp = -1;
			}

			switch (cdp->cd_kind) {
			case CTF_K_INTEGER:
			case CTF_K_FLOAT:
			case CTF_K_TYPEDEF:
				if (qname != NULL)
					ctf_decl_sprintf(&cd, "%s`", qname);
				ctf_decl_sprintf(&cd, "%s", name);
				break;
			case CTF_K_POINTER:
				ctf_decl_sprintf(&cd, "*");
				break;
			case CTF_K_ARRAY:
				ctf_decl_sprintf(&cd, "[%u]", cdp->cd_n);
				break;
			case CTF_K_FUNCTION:
				ctf_decl_sprintf(&cd, "()");
				break;
			case CTF_K_STRUCT:
			case CTF_K_FORWARD:
				ctf_decl_sprintf(&cd, "struct ");
				if (qname != NULL)
					ctf_decl_sprintf(&cd, "%s`", qname);
				ctf_decl_sprintf(&cd, "%s", name);
				break;
			case CTF_K_UNION:
				ctf_decl_sprintf(&cd, "union ");
				if (qname != NULL)
					ctf_decl_sprintf(&cd, "%s`", qname);
				ctf_decl_sprintf(&cd, "%s", name);
				break;
			case CTF_K_ENUM:
				ctf_decl_sprintf(&cd, "enum ");
				if (qname != NULL)
					ctf_decl_sprintf(&cd, "%s`", qname);
				ctf_decl_sprintf(&cd, "%s", name);
				break;
			case CTF_K_VOLATILE:
				ctf_decl_sprintf(&cd, "volatile");
				break;
			case CTF_K_CONST:
				ctf_decl_sprintf(&cd, "const");
				break;
			case CTF_K_RESTRICT:
				ctf_decl_sprintf(&cd, "restrict");
				break;
			}

			k = cdp->cd_kind;
		}

		if (rp == prec)
			ctf_decl_sprintf(&cd, ")");
	}

	if (cd.cd_len >= len)
		(void) ctf_set_errno(fp, ECTF_NAMELEN);

	ctf_decl_fini(&cd);
	return (cd.cd_len);
}