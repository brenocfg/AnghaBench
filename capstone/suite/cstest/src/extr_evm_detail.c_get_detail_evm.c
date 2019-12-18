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
typedef  int /*<<< orphan*/  csh ;
typedef  int /*<<< orphan*/  cs_mode ;
struct TYPE_6__ {TYPE_1__* detail; } ;
typedef  TYPE_2__ cs_insn ;
struct TYPE_7__ {scalar_t__ fee; scalar_t__ push; scalar_t__ pop; } ;
typedef  TYPE_3__ cs_evm ;
struct TYPE_5__ {TYPE_3__ evm; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_str (char**,char*,scalar_t__) ; 
 scalar_t__ malloc (int) ; 

char *get_detail_evm(csh *handle, cs_mode mode, cs_insn *ins)
{
	cs_evm *evm;
	char *result;

	result = (char *)malloc(sizeof(char));
	result[0] = '\0';

	if (ins->detail == NULL)
		return result;

	evm = &(ins->detail->evm);

	if (evm->pop)
		add_str(&result, " ; Pop: %u", evm->pop);

	if (evm->push)
		add_str(&result, " ; Push: %u", evm->push);

	if (evm->fee)
		add_str(&result, " ; Gas fee: %u", evm->fee);

	return result;
}