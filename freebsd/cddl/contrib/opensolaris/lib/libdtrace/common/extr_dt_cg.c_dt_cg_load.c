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
typedef  int /*<<< orphan*/  const uint_t ;
typedef  int ssize_t ;
struct TYPE_5__ {int dn_flags; } ;
typedef  TYPE_1__ dt_node_t ;
typedef  int /*<<< orphan*/  ctf_id_t ;
typedef  int /*<<< orphan*/  ctf_file_t ;
struct TYPE_6__ {int /*<<< orphan*/  cte_bits; } ;
typedef  TYPE_2__ ctf_encoding_t ;

/* Variables and functions */
 scalar_t__ CTF_ERR ; 
#define  DIF_OP_LDSB 141 
#define  DIF_OP_LDSH 140 
#define  DIF_OP_LDSW 139 
#define  DIF_OP_LDUB 138 
#define  DIF_OP_LDUH 137 
#define  DIF_OP_LDUW 136 
#define  DIF_OP_LDX 135 
#define  DIF_OP_ULDSB 134 
#define  DIF_OP_ULDSH 133 
#define  DIF_OP_ULDSW 132 
#define  DIF_OP_ULDUB 131 
#define  DIF_OP_ULDUH 130 
#define  DIF_OP_ULDUW 129 
#define  DIF_OP_ULDX 128 
 int DT_NF_BITFIELD ; 
 int DT_NF_SIGNED ; 
 int DT_NF_USERLAND ; 
 int /*<<< orphan*/  D_UNKNOWN ; 
 int NBBY ; 
 int P2ROUNDUP (int /*<<< orphan*/ ,int) ; 
 int clp2 (int) ; 
 scalar_t__ ctf_type_encoding (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int ctf_type_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xyerror (int /*<<< orphan*/ ,char*,long) ; 

__attribute__((used)) static uint_t
dt_cg_load(dt_node_t *dnp, ctf_file_t *ctfp, ctf_id_t type)
{
	static const uint_t ops[] = {
		DIF_OP_LDUB,	DIF_OP_LDUH,	0,	DIF_OP_LDUW,
		0,		0,		0,	DIF_OP_LDX,
		DIF_OP_LDSB,	DIF_OP_LDSH,	0,	DIF_OP_LDSW,
		0,		0,		0,	DIF_OP_LDX,
		DIF_OP_ULDUB,	DIF_OP_ULDUH,	0,	DIF_OP_ULDUW,
		0,		0,		0,	DIF_OP_ULDX,
		DIF_OP_ULDSB,	DIF_OP_ULDSH,	0,	DIF_OP_ULDSW,
		0,		0,		0,	DIF_OP_ULDX,
	};

	ctf_encoding_t e;
	ssize_t size;

	/*
	 * If we're loading a bit-field, the size of our load is found by
	 * rounding cte_bits up to a byte boundary and then finding the
	 * nearest power of two to this value (see clp2(), above).
	 */
	if ((dnp->dn_flags & DT_NF_BITFIELD) &&
	    ctf_type_encoding(ctfp, type, &e) != CTF_ERR)
		size = clp2(P2ROUNDUP(e.cte_bits, NBBY) / NBBY);
	else
		size = ctf_type_size(ctfp, type);

	if (size < 1 || size > 8 || (size & (size - 1)) != 0) {
		xyerror(D_UNKNOWN, "internal error -- cg cannot load "
		    "size %ld when passed by value\n", (long)size);
	}

	size--; /* convert size to 3-bit index */

	if (dnp->dn_flags & DT_NF_SIGNED)
		size |= 0x08;
	if (dnp->dn_flags & DT_NF_USERLAND)
		size |= 0x10;

	return (ops[size]);
}