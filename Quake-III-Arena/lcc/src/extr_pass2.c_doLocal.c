#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* rcc_interface_ty ;
struct TYPE_9__ {scalar_t__ scope; } ;
struct TYPE_7__ {int uid; TYPE_4__* p; } ;
struct TYPE_6__ {TYPE_2__ rcc_Local; } ;
struct TYPE_8__ {TYPE_1__ v; } ;

/* Variables and functions */
 scalar_t__ LOCAL ; 
 int /*<<< orphan*/  addlocal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ ** items ; 
 int nuids ; 
 int /*<<< orphan*/ * rcc_Symbol (int,TYPE_4__*) ; 
 int /*<<< orphan*/  uid2symbol (int) ; 

__attribute__((used)) static void doLocal(rcc_interface_ty in) {
	int uid = in->v.rcc_Local.uid;

	assert(uid >= 0 && uid < nuids);
	assert(items[uid] == NULL);
	items[uid] = rcc_Symbol(uid, in->v.rcc_Local.p);
	if (in->v.rcc_Local.p->scope >= LOCAL)
		addlocal(uid2symbol(uid));
}