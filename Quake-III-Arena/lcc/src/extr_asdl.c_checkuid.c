#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* rcc_interface_ty ;
typedef  int /*<<< orphan*/  list_ty ;
struct TYPE_5__ {int /*<<< orphan*/  codelist; } ;
struct TYPE_6__ {TYPE_1__ rcc_Function; } ;
struct TYPE_7__ {scalar_t__ kind; TYPE_2__ v; } ;

/* Variables and functions */
 TYPE_3__* Seq_get (int /*<<< orphan*/ ,int) ; 
 int Seq_length (int /*<<< orphan*/ ) ; 
 scalar_t__ rcc_Address_enum ; 
 scalar_t__ rcc_Function_enum ; 
 scalar_t__ rcc_Local_enum ; 

__attribute__((used)) static int checkuid(list_ty list) {
	int i, n = 0, count = Seq_length(list);

	for (i = 0; i < count; i++) {
		rcc_interface_ty in = Seq_get(list, i);
		if (in->kind == rcc_Local_enum
		||  in->kind == rcc_Address_enum)
			n++;
		else if (in->kind == rcc_Function_enum)
			n += checkuid(in->v.rcc_Function.codelist);
	}
	return n;
}