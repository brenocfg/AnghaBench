#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  char* uintmax_t ;
typedef  char uint8_t ;
typedef  int uint64_t ;
struct section {int /*<<< orphan*/  scn; int /*<<< orphan*/ * name; } ;
struct readelf {size_t shnum; int (* dw_read ) (TYPE_1__*,int*,int) ;int (* dw_decode ) (char**,scalar_t__) ;int /*<<< orphan*/  dbg; struct section* sl; } ;
typedef  char* intmax_t ;
typedef  int int8_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_13__ {scalar_t__ d_size; scalar_t__ d_buf; } ;
typedef  TYPE_1__ Elf_Data ;
typedef  int Dwarf_Unsigned ;
typedef  int Dwarf_Small ;
typedef  scalar_t__ Dwarf_Half ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  int /*<<< orphan*/ * Dwarf_Die ;

/* Variables and functions */
 int ADDRESS (char) ; 
 int /*<<< orphan*/  DW_AT_stmt_list ; 
 int DW_DLV_ERROR ; 
 int DW_DLV_OK ; 
#define  DW_LNE_define_file 142 
#define  DW_LNE_end_sequence 141 
#define  DW_LNE_set_address 140 
#define  DW_LNS_advance_line 139 
#define  DW_LNS_advance_pc 138 
#define  DW_LNS_const_add_pc 137 
#define  DW_LNS_copy 136 
#define  DW_LNS_fixed_advance_pc 135 
#define  DW_LNS_negate_stmt 134 
#define  DW_LNS_set_basic_block 133 
#define  DW_LNS_set_column 132 
#define  DW_LNS_set_epilogue_begin 131 
#define  DW_LNS_set_file 130 
#define  DW_LNS_set_isa 129 
#define  DW_LNS_set_prologue_end 128 
 scalar_t__ DW_TAG_compile_unit ; 
 int LINE (char) ; 
 int /*<<< orphan*/  RESET_REGISTERS ; 
 scalar_t__ _decode_sleb128 (char**,char*) ; 
 int _decode_uleb128 (char**,char*) ; 
 int dwarf_attrval_unsigned (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarf_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwarf_get_address_size (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int dwarf_next_cu_header (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dwarf_siblingof (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int dwarf_tag (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 int elf_errno () ; 
 TYPE_1__* elf_getdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ strlen (char*) ; 
 int stub1 (TYPE_1__*,int*,int) ; 
 int stub10 (TYPE_1__*,int*,int) ; 
 int stub11 (char**,scalar_t__) ; 
 int stub12 (char**,int) ; 
 int stub2 (TYPE_1__*,int*,int) ; 
 scalar_t__ stub3 (TYPE_1__*,int*,int) ; 
 int stub4 (TYPE_1__*,int*,int) ; 
 int stub5 (TYPE_1__*,int*,int) ; 
 int stub6 (TYPE_1__*,int*,int) ; 
 int stub7 (TYPE_1__*,int*,int) ; 
 int stub8 (TYPE_1__*,int*,int) ; 
 int stub9 (TYPE_1__*,int*,int) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static void
dump_dwarf_line(struct readelf *re)
{
	struct section *s;
	Dwarf_Die die;
	Dwarf_Error de;
	Dwarf_Half tag, version, pointer_size;
	Dwarf_Unsigned offset, endoff, length, hdrlen, dirndx, mtime, fsize;
	Dwarf_Small minlen, defstmt, lrange, opbase, oplen;
	Elf_Data *d;
	char *pn;
	uint64_t address, file, line, column, isa, opsize, udelta;
	int64_t sdelta;
	uint8_t *p, *pe;
	int8_t lbase;
	int i, is_stmt, dwarf_size, elferr, ret;

	printf("\nDump of debug contents of section .debug_line:\n");

	s = NULL;
	for (i = 0; (size_t) i < re->shnum; i++) {
		s = &re->sl[i];
		if (s->name != NULL && !strcmp(s->name, ".debug_line"))
			break;
	}
	if ((size_t) i >= re->shnum)
		return;

	(void) elf_errno();
	if ((d = elf_getdata(s->scn, NULL)) == NULL) {
		elferr = elf_errno();
		if (elferr != 0)
			warnx("elf_getdata failed: %s", elf_errmsg(-1));
		return;
	}
	if (d->d_size <= 0)
		return;

	while ((ret = dwarf_next_cu_header(re->dbg, NULL, NULL, NULL, NULL,
	    NULL, &de)) ==  DW_DLV_OK) {
		die = NULL;
		while (dwarf_siblingof(re->dbg, die, &die, &de) == DW_DLV_OK) {
			if (dwarf_tag(die, &tag, &de) != DW_DLV_OK) {
				warnx("dwarf_tag failed: %s",
				    dwarf_errmsg(de));
				return;
			}
			/* XXX: What about DW_TAG_partial_unit? */
			if (tag == DW_TAG_compile_unit)
				break;
		}
		if (die == NULL) {
			warnx("could not find DW_TAG_compile_unit die");
			return;
		}
		if (dwarf_attrval_unsigned(die, DW_AT_stmt_list, &offset,
		    &de) != DW_DLV_OK)
			continue;

		length = re->dw_read(d, &offset, 4);
		if (length == 0xffffffff) {
			dwarf_size = 8;
			length = re->dw_read(d, &offset, 8);
		} else
			dwarf_size = 4;

		if (length > d->d_size - offset) {
			warnx("invalid .dwarf_line section");
			continue;
		}

		endoff = offset + length;
		pe = (uint8_t *) d->d_buf + endoff;
		version = re->dw_read(d, &offset, 2);
		hdrlen = re->dw_read(d, &offset, dwarf_size);
		minlen = re->dw_read(d, &offset, 1);
		defstmt = re->dw_read(d, &offset, 1);
		lbase = re->dw_read(d, &offset, 1);
		lrange = re->dw_read(d, &offset, 1);
		opbase = re->dw_read(d, &offset, 1);

		printf("\n");
		printf("  Length:\t\t\t%ju\n", (uintmax_t) length);
		printf("  DWARF version:\t\t%u\n", version);
		printf("  Prologue Length:\t\t%ju\n", (uintmax_t) hdrlen);
		printf("  Minimum Instruction Length:\t%u\n", minlen);
		printf("  Initial value of 'is_stmt':\t%u\n", defstmt);
		printf("  Line Base:\t\t\t%d\n", lbase);
		printf("  Line Range:\t\t\t%u\n", lrange);
		printf("  Opcode Base:\t\t\t%u\n", opbase);
		(void) dwarf_get_address_size(re->dbg, &pointer_size, &de);
		printf("  (Pointer size:\t\t%u)\n", pointer_size);

		printf("\n");
		printf(" Opcodes:\n");
		for (i = 1; i < opbase; i++) {
			oplen = re->dw_read(d, &offset, 1);
			printf("  Opcode %d has %u args\n", i, oplen);
		}

		printf("\n");
		printf(" The Directory Table:\n");
		p = (uint8_t *) d->d_buf + offset;
		while (*p != '\0') {
			printf("  %s\n", (char *) p);
			p += strlen((char *) p) + 1;
		}

		p++;
		printf("\n");
		printf(" The File Name Table:\n");
		printf("  Entry\tDir\tTime\tSize\tName\n");
		i = 0;
		while (*p != '\0') {
			i++;
			pn = (char *) p;
			p += strlen(pn) + 1;
			dirndx = _decode_uleb128(&p, pe);
			mtime = _decode_uleb128(&p, pe);
			fsize = _decode_uleb128(&p, pe);
			printf("  %d\t%ju\t%ju\t%ju\t%s\n", i,
			    (uintmax_t) dirndx, (uintmax_t) mtime,
			    (uintmax_t) fsize, pn);
		}

#define	RESET_REGISTERS						\
	do {							\
		address	       = 0;				\
		file	       = 1;				\
		line	       = 1;				\
		column	       = 0;				\
		is_stmt	       = defstmt;			\
	} while(0)

#define	LINE(x) (lbase + (((x) - opbase) % lrange))
#define	ADDRESS(x) ((((x) - opbase) / lrange) * minlen)

		p++;
		printf("\n");
		printf(" Line Number Statements:\n");

		RESET_REGISTERS;

		while (p < pe) {

			if (*p == 0) {
				/*
				 * Extended Opcodes.
				 */
				p++;
				opsize = _decode_uleb128(&p, pe);
				printf("  Extended opcode %u: ", *p);
				switch (*p) {
				case DW_LNE_end_sequence:
					p++;
					RESET_REGISTERS;
					printf("End of Sequence\n");
					break;
				case DW_LNE_set_address:
					p++;
					address = re->dw_decode(&p,
					    pointer_size);
					printf("set Address to %#jx\n",
					    (uintmax_t) address);
					break;
				case DW_LNE_define_file:
					p++;
					pn = (char *) p;
					p += strlen(pn) + 1;
					dirndx = _decode_uleb128(&p, pe);
					mtime = _decode_uleb128(&p, pe);
					fsize = _decode_uleb128(&p, pe);
					printf("define new file: %s\n", pn);
					break;
				default:
					/* Unrecognized extened opcodes. */
					p += opsize;
					printf("unknown opcode\n");
				}
			} else if (*p > 0 && *p < opbase) {
				/*
				 * Standard Opcodes.
				 */
				switch(*p++) {
				case DW_LNS_copy:
					printf("  Copy\n");
					break;
				case DW_LNS_advance_pc:
					udelta = _decode_uleb128(&p, pe) *
					    minlen;
					address += udelta;
					printf("  Advance PC by %ju to %#jx\n",
					    (uintmax_t) udelta,
					    (uintmax_t) address);
					break;
				case DW_LNS_advance_line:
					sdelta = _decode_sleb128(&p, pe);
					line += sdelta;
					printf("  Advance Line by %jd to %ju\n",
					    (intmax_t) sdelta,
					    (uintmax_t) line);
					break;
				case DW_LNS_set_file:
					file = _decode_uleb128(&p, pe);
					printf("  Set File to %ju\n",
					    (uintmax_t) file);
					break;
				case DW_LNS_set_column:
					column = _decode_uleb128(&p, pe);
					printf("  Set Column to %ju\n",
					    (uintmax_t) column);
					break;
				case DW_LNS_negate_stmt:
					is_stmt = !is_stmt;
					printf("  Set is_stmt to %d\n", is_stmt);
					break;
				case DW_LNS_set_basic_block:
					printf("  Set basic block flag\n");
					break;
				case DW_LNS_const_add_pc:
					address += ADDRESS(255);
					printf("  Advance PC by constant %ju"
					    " to %#jx\n",
					    (uintmax_t) ADDRESS(255),
					    (uintmax_t) address);
					break;
				case DW_LNS_fixed_advance_pc:
					udelta = re->dw_decode(&p, 2);
					address += udelta;
					printf("  Advance PC by fixed value "
					    "%ju to %#jx\n",
					    (uintmax_t) udelta,
					    (uintmax_t) address);
					break;
				case DW_LNS_set_prologue_end:
					printf("  Set prologue end flag\n");
					break;
				case DW_LNS_set_epilogue_begin:
					printf("  Set epilogue begin flag\n");
					break;
				case DW_LNS_set_isa:
					isa = _decode_uleb128(&p, pe);
					printf("  Set isa to %ju\n",
					    (uintmax_t) isa);
					break;
				default:
					/* Unrecognized extended opcodes. */
					printf("  Unknown extended opcode %u\n",
					    *(p - 1));
					break;
				}

			} else {
				/*
				 * Special Opcodes.
				 */
				line += LINE(*p);
				address += ADDRESS(*p);
				printf("  Special opcode %u: advance Address "
				    "by %ju to %#jx and Line by %jd to %ju\n",
				    *p - opbase, (uintmax_t) ADDRESS(*p),
				    (uintmax_t) address, (intmax_t) LINE(*p),
				    (uintmax_t) line);
				p++;
			}


		}
	}
	if (ret == DW_DLV_ERROR)
		warnx("dwarf_next_cu_header: %s", dwarf_errmsg(de));

#undef	RESET_REGISTERS
#undef	LINE
#undef	ADDRESS
}