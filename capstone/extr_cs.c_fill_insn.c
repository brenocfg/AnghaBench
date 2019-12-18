#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct TYPE_6__ {scalar_t__ id; char* mnemonic; } ;
struct insn_mnem {struct insn_mnem* next; TYPE_1__ insn; } ;
struct cs_struct {struct insn_mnem* mnem_list; } ;
typedef  int /*<<< orphan*/  csh ;
struct TYPE_7__ {int size; scalar_t__ id; char* mnemonic; char* op_str; int /*<<< orphan*/  bytes; } ;
typedef  TYPE_2__ cs_insn ;
typedef  int /*<<< orphan*/  (* PostPrinter_t ) (int /*<<< orphan*/ ,TYPE_2__*,char*,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  MCInst ;

/* Variables and functions */
 scalar_t__ MCInst_getOpcodePub (int /*<<< orphan*/ *) ; 
 int MIN (int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static void fill_insn(struct cs_struct *handle, cs_insn *insn, char *buffer, MCInst *mci,
		PostPrinter_t postprinter, const uint8_t *code)
{
#ifndef CAPSTONE_DIET
	char *sp, *mnem;
#endif
	uint16_t copy_size = MIN(sizeof(insn->bytes), insn->size);

	// fill the instruction bytes.
	// we might skip some redundant bytes in front in the case of X86
	memcpy(insn->bytes, code + insn->size - copy_size, copy_size);
	insn->size = copy_size;

	// alias instruction might have ID saved in OpcodePub
	if (MCInst_getOpcodePub(mci))
		insn->id = MCInst_getOpcodePub(mci);

	// post printer handles some corner cases (hacky)
	if (postprinter)
		postprinter((csh)handle, insn, buffer, mci);

#ifndef CAPSTONE_DIET
	// fill in mnemonic & operands
	// find first space or tab
	mnem = insn->mnemonic;
	for (sp = buffer; *sp; sp++) {
		if (*sp == ' '|| *sp == '\t')
			break;
		if (*sp == '|')	// lock|rep prefix for x86
			*sp = ' ';
		// copy to @mnemonic
		*mnem = *sp;
		mnem++;
	}

	*mnem = '\0';

	// we might have customized mnemonic
	if (handle->mnem_list) {
		struct insn_mnem *tmp = handle->mnem_list;
		while(tmp) {
			if (tmp->insn.id == insn->id) {
				// found this instruction, so copy its mnemonic
				(void)strncpy(insn->mnemonic, tmp->insn.mnemonic, sizeof(insn->mnemonic) - 1);
				insn->mnemonic[sizeof(insn->mnemonic) - 1] = '\0';
				break;
			}
			tmp = tmp->next;
		}
	}

	// copy @op_str
	if (*sp) {
		// find the next non-space char
		sp++;
		for (; ((*sp == ' ') || (*sp == '\t')); sp++);
		strncpy(insn->op_str, sp, sizeof(insn->op_str) - 1);
		insn->op_str[sizeof(insn->op_str) - 1] = '\0';
	} else
		insn->op_str[0] = '\0';
#endif
}