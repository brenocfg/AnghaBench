#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char intr_iformat; int intr_signed; int /*<<< orphan*/  intr_fformat; void* intr_type; } ;
typedef  TYPE_1__ intr_t ;
typedef  int /*<<< orphan*/  dwarf_t ;
typedef  int Dwarf_Signed ;
typedef  int /*<<< orphan*/  Dwarf_Off ;
typedef  int /*<<< orphan*/  Dwarf_Die ;

/* Variables and functions */
#define  DW_ATE_SUN_imaginary_float 138 
#define  DW_ATE_SUN_interval_float 137 
#define  DW_ATE_address 136 
#define  DW_ATE_boolean 135 
#define  DW_ATE_complex_float 134 
#define  DW_ATE_float 133 
#define  DW_ATE_imaginary_float 132 
#define  DW_ATE_signed 131 
#define  DW_ATE_signed_char 130 
#define  DW_ATE_unsigned 129 
#define  DW_ATE_unsigned_char 128 
 int /*<<< orphan*/  DW_ATTR_REQ ; 
 int /*<<< orphan*/  DW_AT_encoding ; 
 void* INTR_INT ; 
 void* INTR_REAL ; 
 int /*<<< orphan*/  die_base_type2enc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,size_t) ; 
 int /*<<< orphan*/  die_signed (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  terminate (char*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* xcalloc (int) ; 

__attribute__((used)) static intr_t *
die_base_from_dwarf(dwarf_t *dw, Dwarf_Die base, Dwarf_Off off, size_t sz)
{
	intr_t *intr = xcalloc(sizeof (intr_t));
	Dwarf_Signed enc;

	(void) die_signed(dw, base, DW_AT_encoding, &enc, DW_ATTR_REQ);

	switch (enc) {
	case DW_ATE_unsigned:
	case DW_ATE_address:
		intr->intr_type = INTR_INT;
		break;
	case DW_ATE_unsigned_char:
		intr->intr_type = INTR_INT;
		intr->intr_iformat = 'c';
		break;
	case DW_ATE_signed:
		intr->intr_type = INTR_INT;
		intr->intr_signed = 1;
		break;
	case DW_ATE_signed_char:
		intr->intr_type = INTR_INT;
		intr->intr_signed = 1;
		intr->intr_iformat = 'c';
		break;
	case DW_ATE_boolean:
		intr->intr_type = INTR_INT;
		intr->intr_signed = 1;
		intr->intr_iformat = 'b';
		break;
	case DW_ATE_float:
	case DW_ATE_complex_float:
	case DW_ATE_imaginary_float:
#ifdef illumos
	case DW_ATE_SUN_imaginary_float:
	case DW_ATE_SUN_interval_float:
#endif
		intr->intr_type = INTR_REAL;
		intr->intr_signed = 1;
		intr->intr_fformat = die_base_type2enc(dw, off, enc, sz);
		break;
	default:
		terminate("die %llu: unknown base type encoding 0x%llx\n",
		    off, enc);
	}

	return (intr);
}