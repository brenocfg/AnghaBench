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
struct objfile {int /*<<< orphan*/  obfd; } ;
struct dwarf_block {int size; char* data; } ;
struct comp_unit_head {int dummy; } ;
struct dwarf2_cu {struct comp_unit_head header; struct objfile* objfile; } ;
typedef  unsigned int CORE_ADDR ;

/* Variables and functions */
#define  DW_OP_GNU_push_tls_address 208 
#define  DW_OP_GNU_uninit 207 
#define  DW_OP_addr 206 
#define  DW_OP_const1s 205 
#define  DW_OP_const1u 204 
#define  DW_OP_const2s 203 
#define  DW_OP_const2u 202 
#define  DW_OP_const4s 201 
#define  DW_OP_const4u 200 
#define  DW_OP_consts 199 
#define  DW_OP_constu 198 
#define  DW_OP_deref 197 
#define  DW_OP_dup 196 
#define  DW_OP_lit0 195 
#define  DW_OP_lit1 194 
#define  DW_OP_lit10 193 
#define  DW_OP_lit11 192 
#define  DW_OP_lit12 191 
#define  DW_OP_lit13 190 
#define  DW_OP_lit14 189 
#define  DW_OP_lit15 188 
#define  DW_OP_lit16 187 
#define  DW_OP_lit17 186 
#define  DW_OP_lit18 185 
#define  DW_OP_lit19 184 
#define  DW_OP_lit2 183 
#define  DW_OP_lit20 182 
#define  DW_OP_lit21 181 
#define  DW_OP_lit22 180 
#define  DW_OP_lit23 179 
#define  DW_OP_lit24 178 
#define  DW_OP_lit25 177 
#define  DW_OP_lit26 176 
#define  DW_OP_lit27 175 
#define  DW_OP_lit28 174 
#define  DW_OP_lit29 173 
#define  DW_OP_lit3 172 
#define  DW_OP_lit30 171 
#define  DW_OP_lit31 170 
#define  DW_OP_lit4 169 
#define  DW_OP_lit5 168 
#define  DW_OP_lit6 167 
#define  DW_OP_lit7 166 
#define  DW_OP_lit8 165 
#define  DW_OP_lit9 164 
#define  DW_OP_minus 163 
#define  DW_OP_plus 162 
#define  DW_OP_plus_uconst 161 
#define  DW_OP_reg0 160 
#define  DW_OP_reg1 159 
#define  DW_OP_reg10 158 
#define  DW_OP_reg11 157 
#define  DW_OP_reg12 156 
#define  DW_OP_reg13 155 
#define  DW_OP_reg14 154 
#define  DW_OP_reg15 153 
#define  DW_OP_reg16 152 
#define  DW_OP_reg17 151 
#define  DW_OP_reg18 150 
#define  DW_OP_reg19 149 
#define  DW_OP_reg2 148 
#define  DW_OP_reg20 147 
#define  DW_OP_reg21 146 
#define  DW_OP_reg22 145 
#define  DW_OP_reg23 144 
#define  DW_OP_reg24 143 
#define  DW_OP_reg25 142 
#define  DW_OP_reg26 141 
#define  DW_OP_reg27 140 
#define  DW_OP_reg28 139 
#define  DW_OP_reg29 138 
#define  DW_OP_reg3 137 
#define  DW_OP_reg30 136 
#define  DW_OP_reg31 135 
#define  DW_OP_reg4 134 
#define  DW_OP_reg5 133 
#define  DW_OP_reg6 132 
#define  DW_OP_reg7 131 
#define  DW_OP_reg8 130 
#define  DW_OP_reg9 129 
#define  DW_OP_regx 128 
 int /*<<< orphan*/  complaint (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwarf2_complex_location_expr_complaint () ; 
 int /*<<< orphan*/  dwarf_stack_op_name (unsigned char) ; 
 int isreg ; 
 unsigned int read_1_byte (int /*<<< orphan*/ ,char*) ; 
 unsigned int read_1_signed_byte (int /*<<< orphan*/ ,char*) ; 
 unsigned int read_2_bytes (int /*<<< orphan*/ ,char*) ; 
 unsigned int read_2_signed_bytes (int /*<<< orphan*/ ,char*) ; 
 unsigned int read_4_bytes (int /*<<< orphan*/ ,char*) ; 
 unsigned int read_4_signed_bytes (int /*<<< orphan*/ ,char*) ; 
 unsigned int read_address (int /*<<< orphan*/ ,char*,struct dwarf2_cu*,unsigned int*) ; 
 unsigned int read_signed_leb128 (int /*<<< orphan*/ *,char*,unsigned int*) ; 
 void* read_unsigned_leb128 (int /*<<< orphan*/ *,char*,unsigned int*) ; 
 int /*<<< orphan*/  symfile_complaints ; 

__attribute__((used)) static CORE_ADDR
decode_locdesc (struct dwarf_block *blk, struct dwarf2_cu *cu)
{
  struct objfile *objfile = cu->objfile;
  struct comp_unit_head *cu_header = &cu->header;
  int i;
  int size = blk->size;
  char *data = blk->data;
  CORE_ADDR stack[64];
  int stacki;
  unsigned int bytes_read, unsnd;
  unsigned char op;

  i = 0;
  stacki = 0;
  stack[stacki] = 0;
  isreg = 0;

  while (i < size)
    {
      op = data[i++];
      switch (op)
	{
	case DW_OP_lit0:
	case DW_OP_lit1:
	case DW_OP_lit2:
	case DW_OP_lit3:
	case DW_OP_lit4:
	case DW_OP_lit5:
	case DW_OP_lit6:
	case DW_OP_lit7:
	case DW_OP_lit8:
	case DW_OP_lit9:
	case DW_OP_lit10:
	case DW_OP_lit11:
	case DW_OP_lit12:
	case DW_OP_lit13:
	case DW_OP_lit14:
	case DW_OP_lit15:
	case DW_OP_lit16:
	case DW_OP_lit17:
	case DW_OP_lit18:
	case DW_OP_lit19:
	case DW_OP_lit20:
	case DW_OP_lit21:
	case DW_OP_lit22:
	case DW_OP_lit23:
	case DW_OP_lit24:
	case DW_OP_lit25:
	case DW_OP_lit26:
	case DW_OP_lit27:
	case DW_OP_lit28:
	case DW_OP_lit29:
	case DW_OP_lit30:
	case DW_OP_lit31:
	  stack[++stacki] = op - DW_OP_lit0;
	  break;

	case DW_OP_reg0:
	case DW_OP_reg1:
	case DW_OP_reg2:
	case DW_OP_reg3:
	case DW_OP_reg4:
	case DW_OP_reg5:
	case DW_OP_reg6:
	case DW_OP_reg7:
	case DW_OP_reg8:
	case DW_OP_reg9:
	case DW_OP_reg10:
	case DW_OP_reg11:
	case DW_OP_reg12:
	case DW_OP_reg13:
	case DW_OP_reg14:
	case DW_OP_reg15:
	case DW_OP_reg16:
	case DW_OP_reg17:
	case DW_OP_reg18:
	case DW_OP_reg19:
	case DW_OP_reg20:
	case DW_OP_reg21:
	case DW_OP_reg22:
	case DW_OP_reg23:
	case DW_OP_reg24:
	case DW_OP_reg25:
	case DW_OP_reg26:
	case DW_OP_reg27:
	case DW_OP_reg28:
	case DW_OP_reg29:
	case DW_OP_reg30:
	case DW_OP_reg31:
	  isreg = 1;
	  stack[++stacki] = op - DW_OP_reg0;
	  if (i < size)
	    dwarf2_complex_location_expr_complaint ();
	  break;

	case DW_OP_regx:
	  isreg = 1;
	  unsnd = read_unsigned_leb128 (NULL, (data + i), &bytes_read);
	  i += bytes_read;
	  stack[++stacki] = unsnd;
	  if (i < size)
	    dwarf2_complex_location_expr_complaint ();
	  break;

	case DW_OP_addr:
	  stack[++stacki] = read_address (objfile->obfd, &data[i],
					  cu, &bytes_read);
	  i += bytes_read;
	  break;

	case DW_OP_const1u:
	  stack[++stacki] = read_1_byte (objfile->obfd, &data[i]);
	  i += 1;
	  break;

	case DW_OP_const1s:
	  stack[++stacki] = read_1_signed_byte (objfile->obfd, &data[i]);
	  i += 1;
	  break;

	case DW_OP_const2u:
	  stack[++stacki] = read_2_bytes (objfile->obfd, &data[i]);
	  i += 2;
	  break;

	case DW_OP_const2s:
	  stack[++stacki] = read_2_signed_bytes (objfile->obfd, &data[i]);
	  i += 2;
	  break;

	case DW_OP_const4u:
	  stack[++stacki] = read_4_bytes (objfile->obfd, &data[i]);
	  i += 4;
	  break;

	case DW_OP_const4s:
	  stack[++stacki] = read_4_signed_bytes (objfile->obfd, &data[i]);
	  i += 4;
	  break;

	case DW_OP_constu:
	  stack[++stacki] = read_unsigned_leb128 (NULL, (data + i),
						  &bytes_read);
	  i += bytes_read;
	  break;

	case DW_OP_consts:
	  stack[++stacki] = read_signed_leb128 (NULL, (data + i), &bytes_read);
	  i += bytes_read;
	  break;

	case DW_OP_dup:
	  stack[stacki + 1] = stack[stacki];
	  stacki++;
	  break;

	case DW_OP_plus:
	  stack[stacki - 1] += stack[stacki];
	  stacki--;
	  break;

	case DW_OP_plus_uconst:
	  stack[stacki] += read_unsigned_leb128 (NULL, (data + i), &bytes_read);
	  i += bytes_read;
	  break;

	case DW_OP_minus:
	  stack[stacki - 1] -= stack[stacki];
	  stacki--;
	  break;

	case DW_OP_deref:
	  /* If we're not the last op, then we definitely can't encode
	     this using GDB's address_class enum.  This is valid for partial
	     global symbols, although the variable's address will be bogus
	     in the psymtab.  */
	  if (i < size)
	    dwarf2_complex_location_expr_complaint ();
	  break;

        case DW_OP_GNU_push_tls_address:
	  /* The top of the stack has the offset from the beginning
	     of the thread control block at which the variable is located.  */
	  /* Nothing should follow this operator, so the top of stack would
	     be returned.  */
	  /* This is valid for partial global symbols, but the variable's
	     address will be bogus in the psymtab.  */
	  if (i < size)
	    dwarf2_complex_location_expr_complaint ();
          break;

	case DW_OP_GNU_uninit:
	  break;

	default:
	  complaint (&symfile_complaints, "unsupported stack op: '%s'",
		     dwarf_stack_op_name (op));
	  return (stack[stacki]);
	}
    }
  return (stack[stacki]);
}