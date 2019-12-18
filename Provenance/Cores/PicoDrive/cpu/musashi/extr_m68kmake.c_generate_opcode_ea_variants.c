#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int length; } ;
typedef  TYPE_1__ replace_struct ;
struct TYPE_8__ {int size; int /*<<< orphan*/  ea_allowed; } ;
typedef  TYPE_2__ opcode_struct ;
typedef  int /*<<< orphan*/  body_struct ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EA_MODE_AI ; 
 int /*<<< orphan*/  EA_MODE_AL ; 
 int /*<<< orphan*/  EA_MODE_AW ; 
 int /*<<< orphan*/  EA_MODE_DI ; 
 int /*<<< orphan*/  EA_MODE_I ; 
 int /*<<< orphan*/  EA_MODE_IX ; 
 int /*<<< orphan*/  EA_MODE_NONE ; 
 int /*<<< orphan*/  EA_MODE_PCDI ; 
 int /*<<< orphan*/  EA_MODE_PCIX ; 
 int /*<<< orphan*/  EA_MODE_PD ; 
 int /*<<< orphan*/  EA_MODE_PD7 ; 
 int /*<<< orphan*/  EA_MODE_PI ; 
 int /*<<< orphan*/  EA_MODE_PI7 ; 
 scalar_t__ HAS_EA_AI (int /*<<< orphan*/ ) ; 
 scalar_t__ HAS_EA_AL (int /*<<< orphan*/ ) ; 
 scalar_t__ HAS_EA_AW (int /*<<< orphan*/ ) ; 
 scalar_t__ HAS_EA_DI (int /*<<< orphan*/ ) ; 
 scalar_t__ HAS_EA_I (int /*<<< orphan*/ ) ; 
 scalar_t__ HAS_EA_IX (int /*<<< orphan*/ ) ; 
 scalar_t__ HAS_EA_PCDI (int /*<<< orphan*/ ) ; 
 scalar_t__ HAS_EA_PCIX (int /*<<< orphan*/ ) ; 
 scalar_t__ HAS_EA_PD (int /*<<< orphan*/ ) ; 
 scalar_t__ HAS_EA_PI (int /*<<< orphan*/ ) ; 
 scalar_t__ HAS_NO_EA_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generate_opcode_handler (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 

void generate_opcode_ea_variants(FILE* filep, body_struct* body, replace_struct* replace, opcode_struct* op)
{
	int old_length = replace->length;

	/* No ea modes available for this opcode */
	if(HAS_NO_EA_MODE(op->ea_allowed))
	{
		generate_opcode_handler(filep, body, replace, op, EA_MODE_NONE);
		return;
	}

	/* Check for and create specific opcodes for each available addressing mode */
	if(HAS_EA_AI(op->ea_allowed))
		generate_opcode_handler(filep, body, replace, op, EA_MODE_AI);
	replace->length = old_length;
	if(HAS_EA_PI(op->ea_allowed))
	{
		generate_opcode_handler(filep, body, replace, op, EA_MODE_PI);
		replace->length = old_length;
		if(op->size == 8)
			generate_opcode_handler(filep, body, replace, op, EA_MODE_PI7);
	}
	replace->length = old_length;
	if(HAS_EA_PD(op->ea_allowed))
	{
		generate_opcode_handler(filep, body, replace, op, EA_MODE_PD);
		replace->length = old_length;
		if(op->size == 8)
			generate_opcode_handler(filep, body, replace, op, EA_MODE_PD7);
	}
	replace->length = old_length;
	if(HAS_EA_DI(op->ea_allowed))
		generate_opcode_handler(filep, body, replace, op, EA_MODE_DI);
	replace->length = old_length;
	if(HAS_EA_IX(op->ea_allowed))
		generate_opcode_handler(filep, body, replace, op, EA_MODE_IX);
	replace->length = old_length;
	if(HAS_EA_AW(op->ea_allowed))
		generate_opcode_handler(filep, body, replace, op, EA_MODE_AW);
	replace->length = old_length;
	if(HAS_EA_AL(op->ea_allowed))
		generate_opcode_handler(filep, body, replace, op, EA_MODE_AL);
	replace->length = old_length;
	if(HAS_EA_PCDI(op->ea_allowed))
		generate_opcode_handler(filep, body, replace, op, EA_MODE_PCDI);
	replace->length = old_length;
	if(HAS_EA_PCIX(op->ea_allowed))
		generate_opcode_handler(filep, body, replace, op, EA_MODE_PCIX);
	replace->length = old_length;
	if(HAS_EA_I(op->ea_allowed))
		generate_opcode_handler(filep, body, replace, op, EA_MODE_I);
	replace->length = old_length;
}