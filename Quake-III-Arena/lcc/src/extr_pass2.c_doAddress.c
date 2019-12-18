#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
typedef  TYPE_5__* rcc_interface_ty ;
struct TYPE_13__ {int /*<<< orphan*/  offset; TYPE_6__* base; void* sym; } ;
struct TYPE_14__ {TYPE_1__ addr; } ;
struct TYPE_19__ {TYPE_2__ u; } ;
struct TYPE_18__ {scalar_t__ scope; scalar_t__ sclass; } ;
struct TYPE_15__ {int uid; int p; int /*<<< orphan*/  n; int /*<<< orphan*/  q; } ;
struct TYPE_16__ {TYPE_3__ rcc_Address; } ;
struct TYPE_17__ {TYPE_4__ v; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* address ) (void*,TYPE_6__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_6__* Symbol ;
typedef  TYPE_7__* Code ;

/* Variables and functions */
 int /*<<< orphan*/  Address ; 
 scalar_t__ EXTERN ; 
 scalar_t__ GLOBAL ; 
 TYPE_11__* IR ; 
 scalar_t__ STATIC ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_7__* code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** items ; 
 int nuids ; 
 int /*<<< orphan*/ * rcc_Symbol (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (void*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 void* uid2symbol (int) ; 

__attribute__((used)) static void doAddress(rcc_interface_ty in) {
	int uid = in->v.rcc_Address.uid;
	Symbol p = uid2symbol(in->v.rcc_Address.p);

	assert(uid >= 0 && uid < nuids);
	assert(items[uid] == NULL);
	items[uid] = rcc_Symbol(uid, in->v.rcc_Address.q);
	if (p->scope == GLOBAL || p->sclass == STATIC || p->sclass == EXTERN)
		(*IR->address)(uid2symbol(uid), p, in->v.rcc_Address.n);
	else {
		Code cp = code(Address);
		cp->u.addr.sym = uid2symbol(uid);
		cp->u.addr.base = p;
		cp->u.addr.offset = in->v.rcc_Address.n;
	}
}