#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct isac {int /*<<< orphan*/  hisax_d_if; } ;
struct hisax_if {int /*<<< orphan*/  (* l1l2 ) (struct hisax_if*,int,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  DBG_PR ; 
 int /*<<< orphan*/  stub1 (struct hisax_if*,int,void*) ; 

__attribute__((used)) static inline void D_L1L2(struct isac *isac, int pr, void *arg)
{
	struct hisax_if *ifc = (struct hisax_if *) &isac->hisax_d_if;

	DBG(DBG_PR, "pr %#x", pr);
	ifc->l1l2(ifc, pr, arg);
}