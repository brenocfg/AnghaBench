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
struct _Unwind_Context {int dummy; } ;
typedef  int /*<<< orphan*/  stack ;
typedef  enum dwarf_location_atom { ____Placeholder_dwarf_location_atom } dwarf_location_atom ;
typedef  int _Unwind_Word ;
typedef  int _Unwind_Sword ;
typedef  int _Unwind_Ptr ;

/* Variables and functions */
#define  DW_OP_abs 268 
#define  DW_OP_addr 267 
#define  DW_OP_and 266 
#define  DW_OP_bra 265 
#define  DW_OP_breg0 264 
#define  DW_OP_breg1 263 
#define  DW_OP_breg10 262 
#define  DW_OP_breg11 261 
#define  DW_OP_breg12 260 
#define  DW_OP_breg13 259 
#define  DW_OP_breg14 258 
#define  DW_OP_breg15 257 
#define  DW_OP_breg16 256 
#define  DW_OP_breg17 255 
#define  DW_OP_breg18 254 
#define  DW_OP_breg19 253 
#define  DW_OP_breg2 252 
#define  DW_OP_breg20 251 
#define  DW_OP_breg21 250 
#define  DW_OP_breg22 249 
#define  DW_OP_breg23 248 
#define  DW_OP_breg24 247 
#define  DW_OP_breg25 246 
#define  DW_OP_breg26 245 
#define  DW_OP_breg27 244 
#define  DW_OP_breg28 243 
#define  DW_OP_breg29 242 
#define  DW_OP_breg3 241 
#define  DW_OP_breg30 240 
#define  DW_OP_breg31 239 
#define  DW_OP_breg4 238 
#define  DW_OP_breg5 237 
#define  DW_OP_breg6 236 
#define  DW_OP_breg7 235 
#define  DW_OP_breg8 234 
#define  DW_OP_breg9 233 
#define  DW_OP_bregx 232 
#define  DW_OP_const1s 231 
#define  DW_OP_const1u 230 
#define  DW_OP_const2s 229 
#define  DW_OP_const2u 228 
#define  DW_OP_const4s 227 
#define  DW_OP_const4u 226 
#define  DW_OP_const8s 225 
#define  DW_OP_const8u 224 
#define  DW_OP_consts 223 
#define  DW_OP_constu 222 
#define  DW_OP_deref 221 
#define  DW_OP_deref_size 220 
#define  DW_OP_div 219 
#define  DW_OP_drop 218 
#define  DW_OP_dup 217 
#define  DW_OP_eq 216 
#define  DW_OP_ge 215 
#define  DW_OP_gt 214 
#define  DW_OP_le 213 
#define  DW_OP_lit0 212 
#define  DW_OP_lit1 211 
#define  DW_OP_lit10 210 
#define  DW_OP_lit11 209 
#define  DW_OP_lit12 208 
#define  DW_OP_lit13 207 
#define  DW_OP_lit14 206 
#define  DW_OP_lit15 205 
#define  DW_OP_lit16 204 
#define  DW_OP_lit17 203 
#define  DW_OP_lit18 202 
#define  DW_OP_lit19 201 
#define  DW_OP_lit2 200 
#define  DW_OP_lit20 199 
#define  DW_OP_lit21 198 
#define  DW_OP_lit22 197 
#define  DW_OP_lit23 196 
#define  DW_OP_lit24 195 
#define  DW_OP_lit25 194 
#define  DW_OP_lit26 193 
#define  DW_OP_lit27 192 
#define  DW_OP_lit28 191 
#define  DW_OP_lit29 190 
#define  DW_OP_lit3 189 
#define  DW_OP_lit30 188 
#define  DW_OP_lit31 187 
#define  DW_OP_lit4 186 
#define  DW_OP_lit5 185 
#define  DW_OP_lit6 184 
#define  DW_OP_lit7 183 
#define  DW_OP_lit8 182 
#define  DW_OP_lit9 181 
#define  DW_OP_lt 180 
#define  DW_OP_minus 179 
#define  DW_OP_mod 178 
#define  DW_OP_mul 177 
#define  DW_OP_ne 176 
#define  DW_OP_neg 175 
#define  DW_OP_nop 174 
#define  DW_OP_not 173 
#define  DW_OP_or 172 
#define  DW_OP_over 171 
#define  DW_OP_pick 170 
#define  DW_OP_plus 169 
#define  DW_OP_plus_uconst 168 
#define  DW_OP_reg0 167 
#define  DW_OP_reg1 166 
#define  DW_OP_reg10 165 
#define  DW_OP_reg11 164 
#define  DW_OP_reg12 163 
#define  DW_OP_reg13 162 
#define  DW_OP_reg14 161 
#define  DW_OP_reg15 160 
#define  DW_OP_reg16 159 
#define  DW_OP_reg17 158 
#define  DW_OP_reg18 157 
#define  DW_OP_reg19 156 
#define  DW_OP_reg2 155 
#define  DW_OP_reg20 154 
#define  DW_OP_reg21 153 
#define  DW_OP_reg22 152 
#define  DW_OP_reg23 151 
#define  DW_OP_reg24 150 
#define  DW_OP_reg25 149 
#define  DW_OP_reg26 148 
#define  DW_OP_reg27 147 
#define  DW_OP_reg28 146 
#define  DW_OP_reg29 145 
#define  DW_OP_reg3 144 
#define  DW_OP_reg30 143 
#define  DW_OP_reg31 142 
#define  DW_OP_reg4 141 
#define  DW_OP_reg5 140 
#define  DW_OP_reg6 139 
#define  DW_OP_reg7 138 
#define  DW_OP_reg8 137 
#define  DW_OP_reg9 136 
#define  DW_OP_regx 135 
#define  DW_OP_rot 134 
#define  DW_OP_shl 133 
#define  DW_OP_shr 132 
#define  DW_OP_shra 131 
#define  DW_OP_skip 130 
#define  DW_OP_swap 129 
#define  DW_OP_xor 128 
 int _Unwind_GetGR (struct _Unwind_Context*,int) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int read_1s (unsigned char const*) ; 
 int read_1u (void*) ; 
 int read_2s (unsigned char const*) ; 
 int read_2u (void*) ; 
 int read_4s (unsigned char const*) ; 
 int read_4u (void*) ; 
 int read_8s (unsigned char const*) ; 
 int read_8u (void*) ; 
 int /*<<< orphan*/  read_pointer (void*) ; 
 unsigned char* read_sleb128 (unsigned char const*,int*) ; 
 unsigned char* read_uleb128 (unsigned char const*,int*) ; 

__attribute__((used)) static _Unwind_Word
execute_stack_op (const unsigned char *op_ptr, const unsigned char *op_end,
		  struct _Unwind_Context *context, _Unwind_Word initial)
{
  _Unwind_Word stack[64];	/* ??? Assume this is enough.  */
  int stack_elt;

  stack[0] = initial;
  stack_elt = 1;

  while (op_ptr < op_end)
    {
      enum dwarf_location_atom op = *op_ptr++;
      _Unwind_Word result, reg, utmp;
      _Unwind_Sword offset, stmp;

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
	  result = op - DW_OP_lit0;
	  break;

	case DW_OP_addr:
	  result = (_Unwind_Word) (_Unwind_Ptr) read_pointer (op_ptr);
	  op_ptr += sizeof (void *);
	  break;

	case DW_OP_const1u:
	  result = read_1u (op_ptr);
	  op_ptr += 1;
	  break;
	case DW_OP_const1s:
	  result = read_1s (op_ptr);
	  op_ptr += 1;
	  break;
	case DW_OP_const2u:
	  result = read_2u (op_ptr);
	  op_ptr += 2;
	  break;
	case DW_OP_const2s:
	  result = read_2s (op_ptr);
	  op_ptr += 2;
	  break;
	case DW_OP_const4u:
	  result = read_4u (op_ptr);
	  op_ptr += 4;
	  break;
	case DW_OP_const4s:
	  result = read_4s (op_ptr);
	  op_ptr += 4;
	  break;
	case DW_OP_const8u:
	  result = read_8u (op_ptr);
	  op_ptr += 8;
	  break;
	case DW_OP_const8s:
	  result = read_8s (op_ptr);
	  op_ptr += 8;
	  break;
	case DW_OP_constu:
	  op_ptr = read_uleb128 (op_ptr, &result);
	  break;
	case DW_OP_consts:
	  op_ptr = read_sleb128 (op_ptr, &stmp);
	  result = stmp;
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
	  result = _Unwind_GetGR (context, op - DW_OP_reg0);
	  break;
	case DW_OP_regx:
	  op_ptr = read_uleb128 (op_ptr, &reg);
	  result = _Unwind_GetGR (context, reg);
	  break;

	case DW_OP_breg0:
	case DW_OP_breg1:
	case DW_OP_breg2:
	case DW_OP_breg3:
	case DW_OP_breg4:
	case DW_OP_breg5:
	case DW_OP_breg6:
	case DW_OP_breg7:
	case DW_OP_breg8:
	case DW_OP_breg9:
	case DW_OP_breg10:
	case DW_OP_breg11:
	case DW_OP_breg12:
	case DW_OP_breg13:
	case DW_OP_breg14:
	case DW_OP_breg15:
	case DW_OP_breg16:
	case DW_OP_breg17:
	case DW_OP_breg18:
	case DW_OP_breg19:
	case DW_OP_breg20:
	case DW_OP_breg21:
	case DW_OP_breg22:
	case DW_OP_breg23:
	case DW_OP_breg24:
	case DW_OP_breg25:
	case DW_OP_breg26:
	case DW_OP_breg27:
	case DW_OP_breg28:
	case DW_OP_breg29:
	case DW_OP_breg30:
	case DW_OP_breg31:
	  op_ptr = read_sleb128 (op_ptr, &offset);
	  result = _Unwind_GetGR (context, op - DW_OP_breg0) + offset;
	  break;
	case DW_OP_bregx:
	  op_ptr = read_uleb128 (op_ptr, &reg);
	  op_ptr = read_sleb128 (op_ptr, &offset);
	  result = _Unwind_GetGR (context, reg) + offset;
	  break;

	case DW_OP_dup:
	  gcc_assert (stack_elt);
	  result = stack[stack_elt - 1];
	  break;

	case DW_OP_drop:
	  gcc_assert (stack_elt);
	  stack_elt -= 1;
	  goto no_push;

	case DW_OP_pick:
	  offset = *op_ptr++;
	  gcc_assert (offset < stack_elt - 1);
	  result = stack[stack_elt - 1 - offset];
	  break;

	case DW_OP_over:
	  gcc_assert (stack_elt >= 2);
	  result = stack[stack_elt - 2];
	  break;

	case DW_OP_swap:
	  {
	    _Unwind_Word t;
	    gcc_assert (stack_elt >= 2);
	    t = stack[stack_elt - 1];
	    stack[stack_elt - 1] = stack[stack_elt - 2];
	    stack[stack_elt - 2] = t;
	    goto no_push;
	  }

	case DW_OP_rot:
	  {
	    _Unwind_Word t1, t2, t3;

	    gcc_assert (stack_elt >= 3);
	    t1 = stack[stack_elt - 1];
	    t2 = stack[stack_elt - 2];
	    t3 = stack[stack_elt - 3];
	    stack[stack_elt - 1] = t2;
	    stack[stack_elt - 2] = t3;
	    stack[stack_elt - 3] = t1;
	    goto no_push;
	  }

	case DW_OP_deref:
	case DW_OP_deref_size:
	case DW_OP_abs:
	case DW_OP_neg:
	case DW_OP_not:
	case DW_OP_plus_uconst:
	  /* Unary operations.  */
	  gcc_assert (stack_elt);
	  stack_elt -= 1;
	  
	  result = stack[stack_elt];

	  switch (op)
	    {
	    case DW_OP_deref:
	      {
		void *ptr = (void *) (_Unwind_Ptr) result;
		result = (_Unwind_Ptr) read_pointer (ptr);
	      }
	      break;

	    case DW_OP_deref_size:
	      {
		void *ptr = (void *) (_Unwind_Ptr) result;
		switch (*op_ptr++)
		  {
		  case 1:
		    result = read_1u (ptr);
		    break;
		  case 2:
		    result = read_2u (ptr);
		    break;
		  case 4:
		    result = read_4u (ptr);
		    break;
		  case 8:
		    result = read_8u (ptr);
		    break;
		  default:
		    gcc_unreachable ();
		  }
	      }
	      break;

	    case DW_OP_abs:
	      if ((_Unwind_Sword) result < 0)
		result = -result;
	      break;
	    case DW_OP_neg:
	      result = -result;
	      break;
	    case DW_OP_not:
	      result = ~result;
	      break;
	    case DW_OP_plus_uconst:
	      op_ptr = read_uleb128 (op_ptr, &utmp);
	      result += utmp;
	      break;

	    default:
	      gcc_unreachable ();
	    }
	  break;

	case DW_OP_and:
	case DW_OP_div:
	case DW_OP_minus:
	case DW_OP_mod:
	case DW_OP_mul:
	case DW_OP_or:
	case DW_OP_plus:
	case DW_OP_shl:
	case DW_OP_shr:
	case DW_OP_shra:
	case DW_OP_xor:
	case DW_OP_le:
	case DW_OP_ge:
	case DW_OP_eq:
	case DW_OP_lt:
	case DW_OP_gt:
	case DW_OP_ne:
	  {
	    /* Binary operations.  */
	    _Unwind_Word first, second;
	    gcc_assert (stack_elt >= 2);
	    stack_elt -= 2;
	    
	    second = stack[stack_elt];
	    first = stack[stack_elt + 1];

	    switch (op)
	      {
	      case DW_OP_and:
		result = second & first;
		break;
	      case DW_OP_div:
		result = (_Unwind_Sword) second / (_Unwind_Sword) first;
		break;
	      case DW_OP_minus:
		result = second - first;
		break;
	      case DW_OP_mod:
		result = (_Unwind_Sword) second % (_Unwind_Sword) first;
		break;
	      case DW_OP_mul:
		result = second * first;
		break;
	      case DW_OP_or:
		result = second | first;
		break;
	      case DW_OP_plus:
		result = second + first;
		break;
	      case DW_OP_shl:
		result = second << first;
		break;
	      case DW_OP_shr:
		result = second >> first;
		break;
	      case DW_OP_shra:
		result = (_Unwind_Sword) second >> first;
		break;
	      case DW_OP_xor:
		result = second ^ first;
		break;
	      case DW_OP_le:
		result = (_Unwind_Sword) first <= (_Unwind_Sword) second;
		break;
	      case DW_OP_ge:
		result = (_Unwind_Sword) first >= (_Unwind_Sword) second;
		break;
	      case DW_OP_eq:
		result = (_Unwind_Sword) first == (_Unwind_Sword) second;
		break;
	      case DW_OP_lt:
		result = (_Unwind_Sword) first < (_Unwind_Sword) second;
		break;
	      case DW_OP_gt:
		result = (_Unwind_Sword) first > (_Unwind_Sword) second;
		break;
	      case DW_OP_ne:
		result = (_Unwind_Sword) first != (_Unwind_Sword) second;
		break;

	      default:
		gcc_unreachable ();
	      }
	  }
	  break;

	case DW_OP_skip:
	  offset = read_2s (op_ptr);
	  op_ptr += 2;
	  op_ptr += offset;
	  goto no_push;

	case DW_OP_bra:
	  gcc_assert (stack_elt);
	  stack_elt -= 1;
	  
	  offset = read_2s (op_ptr);
	  op_ptr += 2;
	  if (stack[stack_elt] != 0)
	    op_ptr += offset;
	  goto no_push;

	case DW_OP_nop:
	  goto no_push;

	default:
	  gcc_unreachable ();
	}

      /* Most things push a result value.  */
      gcc_assert ((size_t) stack_elt < sizeof(stack)/sizeof(*stack));
      stack[stack_elt++] = result;
    no_push:;
    }

  /* We were executing this program to get a value.  It should be
     at top of stack.  */
  gcc_assert (stack_elt);
  stack_elt -= 1;
  return stack[stack_elt];
}