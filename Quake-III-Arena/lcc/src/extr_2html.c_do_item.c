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
typedef  TYPE_1__* rcc_item_ty ;
struct TYPE_3__ {int uid; int kind; } ;

/* Variables and functions */
 int /*<<< orphan*/  Symbol ; 
 int /*<<< orphan*/  Type ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caselabel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  symbol ; 
 int /*<<< orphan*/  type ; 
 int /*<<< orphan*/  yy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_item(rcc_item_ty x) {
	printf("<a name='%d'>", x->uid);
#define attributes xx(x,uid,define_uid)
	printf("</a>");
	switch (x->kind) {
	static char *typename = "item";
	caselabel(Symbol);
		yy(Symbol,symbol,symbol);
		break;
	caselabel(Type);
		yy(Type,type,type);
		break;
	default: assert(0);
	}
#undef attributes
	printf("</ul>\n");
}