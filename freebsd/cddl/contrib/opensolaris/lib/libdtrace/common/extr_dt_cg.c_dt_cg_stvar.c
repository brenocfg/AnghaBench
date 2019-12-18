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
typedef  size_t const uint_t ;
struct TYPE_3__ {int di_flags; scalar_t__ di_kind; } ;
typedef  TYPE_1__ dt_ident_t ;

/* Variables and functions */
#define  DIF_OP_NOP 133 
#define  DIF_OP_STGAA 132 
#define  DIF_OP_STGS 131 
#define  DIF_OP_STLS 130 
#define  DIF_OP_STTAA 129 
#define  DIF_OP_STTS 128 
 scalar_t__ DT_IDENT_ARRAY ; 
 int DT_IDFLG_LOCAL ; 
 int DT_IDFLG_TLS ; 

__attribute__((used)) static uint_t
dt_cg_stvar(const dt_ident_t *idp)
{
	static const uint_t aops[] = { DIF_OP_STGAA, DIF_OP_STTAA, DIF_OP_NOP };
	static const uint_t sops[] = { DIF_OP_STGS, DIF_OP_STTS, DIF_OP_STLS };

	uint_t i = (((idp->di_flags & DT_IDFLG_LOCAL) != 0) << 1) |
	    ((idp->di_flags & DT_IDFLG_TLS) != 0);

	return (idp->di_kind == DT_IDENT_ARRAY ? aops[i] : sops[i]);
}