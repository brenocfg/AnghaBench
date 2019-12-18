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
typedef  enum exp_opcode { ____Placeholder_exp_opcode } exp_opcode ;

/* Variables and functions */
#define  BINOP_ADD 213 
#define  BINOP_ASSIGN 212 
#define  BINOP_ASSIGN_MODIFY 211 
#define  BINOP_BITWISE_AND 210 
#define  BINOP_BITWISE_IOR 209 
#define  BINOP_BITWISE_XOR 208 
#define  BINOP_COMMA 207 
#define  BINOP_CONCAT 206 
#define  BINOP_DIV 205 
#define  BINOP_END 204 
#define  BINOP_EQUAL 203 
#define  BINOP_EXCL 202 
#define  BINOP_EXP 201 
#define  BINOP_GEQ 200 
#define  BINOP_GTR 199 
#define  BINOP_INCL 198 
#define  BINOP_INTDIV 197 
#define  BINOP_LEQ 196 
#define  BINOP_LESS 195 
#define  BINOP_LOGICAL_AND 194 
#define  BINOP_LOGICAL_OR 193 
#define  BINOP_LSH 192 
#define  BINOP_MAX 191 
#define  BINOP_MIN 190 
#define  BINOP_MOD 189 
#define  BINOP_MUL 188 
#define  BINOP_NOTEQUAL 187 
#define  BINOP_RANGE 186 
#define  BINOP_REM 185 
#define  BINOP_REPEAT 184 
#define  BINOP_RSH 183 
#define  BINOP_SUB 182 
#define  BINOP_SUBSCRIPT 181 
#define  BINOP_VAL 180 
#define  MULTI_SUBSCRIPT 179 
#define  OP_ARRAY 178 
#define  OP_BITSTRING 177 
#define  OP_BOOL 176 
#define  OP_DOUBLE 175 
#define  OP_FUNCALL 174 
#define  OP_INTERNALVAR 173 
#define  OP_LABELED 172 
#define  OP_LAST 171 
#define  OP_LONG 170 
#define  OP_M2_STRING 169 
#define  OP_NULL 168 
#define  OP_OBJC_SELF 167 
#define  OP_REGISTER 166 
#define  OP_SCOPE 165 
#define  OP_STRING 164 
#define  OP_THIS 163 
#define  OP_TYPE 162 
#define  OP_VAR_VALUE 161 
#define  STRUCTOP_MEMBER 160 
#define  STRUCTOP_MPTR 159 
#define  STRUCTOP_PTR 158 
#define  STRUCTOP_STRUCT 157 
#define  TERNOP_COND 156 
#define  TERNOP_SLICE 155 
#define  TERNOP_SLICE_COUNT 154 
#define  UNOP_ABS 153 
#define  UNOP_ADDR 152 
#define  UNOP_CAP 151 
#define  UNOP_CAST 150 
#define  UNOP_CHR 149 
#define  UNOP_COMPLEMENT 148 
#define  UNOP_FLOAT 147 
#define  UNOP_HIGH 146 
#define  UNOP_IND 145 
#define  UNOP_LENGTH 144 
#define  UNOP_LOGICAL_NOT 143 
#define  UNOP_LOWER 142 
#define  UNOP_MAX 141 
#define  UNOP_MEMVAL 140 
#define  UNOP_MIN 139 
#define  UNOP_NEG 138 
#define  UNOP_ODD 137 
#define  UNOP_ORD 136 
#define  UNOP_PLUS 135 
#define  UNOP_POSTDECREMENT 134 
#define  UNOP_POSTINCREMENT 133 
#define  UNOP_PREDECREMENT 132 
#define  UNOP_PREINCREMENT 131 
#define  UNOP_SIZEOF 130 
#define  UNOP_TRUNC 129 
#define  UNOP_UPPER 128 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

char *
op_name_standard (enum exp_opcode opcode)
{
  switch (opcode)
    {
    default:
      {
	static char buf[30];

	sprintf (buf, "<unknown %d>", opcode);
	return buf;
      }
    case OP_NULL:
      return "OP_NULL";
    case BINOP_ADD:
      return "BINOP_ADD";
    case BINOP_SUB:
      return "BINOP_SUB";
    case BINOP_MUL:
      return "BINOP_MUL";
    case BINOP_DIV:
      return "BINOP_DIV";
    case BINOP_REM:
      return "BINOP_REM";
    case BINOP_MOD:
      return "BINOP_MOD";
    case BINOP_LSH:
      return "BINOP_LSH";
    case BINOP_RSH:
      return "BINOP_RSH";
    case BINOP_LOGICAL_AND:
      return "BINOP_LOGICAL_AND";
    case BINOP_LOGICAL_OR:
      return "BINOP_LOGICAL_OR";
    case BINOP_BITWISE_AND:
      return "BINOP_BITWISE_AND";
    case BINOP_BITWISE_IOR:
      return "BINOP_BITWISE_IOR";
    case BINOP_BITWISE_XOR:
      return "BINOP_BITWISE_XOR";
    case BINOP_EQUAL:
      return "BINOP_EQUAL";
    case BINOP_NOTEQUAL:
      return "BINOP_NOTEQUAL";
    case BINOP_LESS:
      return "BINOP_LESS";
    case BINOP_GTR:
      return "BINOP_GTR";
    case BINOP_LEQ:
      return "BINOP_LEQ";
    case BINOP_GEQ:
      return "BINOP_GEQ";
    case BINOP_REPEAT:
      return "BINOP_REPEAT";
    case BINOP_ASSIGN:
      return "BINOP_ASSIGN";
    case BINOP_COMMA:
      return "BINOP_COMMA";
    case BINOP_SUBSCRIPT:
      return "BINOP_SUBSCRIPT";
    case MULTI_SUBSCRIPT:
      return "MULTI_SUBSCRIPT";
    case BINOP_EXP:
      return "BINOP_EXP";
    case BINOP_MIN:
      return "BINOP_MIN";
    case BINOP_MAX:
      return "BINOP_MAX";
    case STRUCTOP_MEMBER:
      return "STRUCTOP_MEMBER";
    case STRUCTOP_MPTR:
      return "STRUCTOP_MPTR";
    case BINOP_INTDIV:
      return "BINOP_INTDIV";
    case BINOP_ASSIGN_MODIFY:
      return "BINOP_ASSIGN_MODIFY";
    case BINOP_VAL:
      return "BINOP_VAL";
    case BINOP_INCL:
      return "BINOP_INCL";
    case BINOP_EXCL:
      return "BINOP_EXCL";
    case BINOP_CONCAT:
      return "BINOP_CONCAT";
    case BINOP_RANGE:
      return "BINOP_RANGE";
    case BINOP_END:
      return "BINOP_END";
    case TERNOP_COND:
      return "TERNOP_COND";
    case TERNOP_SLICE:
      return "TERNOP_SLICE";
    case TERNOP_SLICE_COUNT:
      return "TERNOP_SLICE_COUNT";
    case OP_LONG:
      return "OP_LONG";
    case OP_DOUBLE:
      return "OP_DOUBLE";
    case OP_VAR_VALUE:
      return "OP_VAR_VALUE";
    case OP_LAST:
      return "OP_LAST";
    case OP_REGISTER:
      return "OP_REGISTER";
    case OP_INTERNALVAR:
      return "OP_INTERNALVAR";
    case OP_FUNCALL:
      return "OP_FUNCALL";
    case OP_STRING:
      return "OP_STRING";
    case OP_BITSTRING:
      return "OP_BITSTRING";
    case OP_ARRAY:
      return "OP_ARRAY";
    case UNOP_CAST:
      return "UNOP_CAST";
    case UNOP_MEMVAL:
      return "UNOP_MEMVAL";
    case UNOP_NEG:
      return "UNOP_NEG";
    case UNOP_LOGICAL_NOT:
      return "UNOP_LOGICAL_NOT";
    case UNOP_COMPLEMENT:
      return "UNOP_COMPLEMENT";
    case UNOP_IND:
      return "UNOP_IND";
    case UNOP_ADDR:
      return "UNOP_ADDR";
    case UNOP_PREINCREMENT:
      return "UNOP_PREINCREMENT";
    case UNOP_POSTINCREMENT:
      return "UNOP_POSTINCREMENT";
    case UNOP_PREDECREMENT:
      return "UNOP_PREDECREMENT";
    case UNOP_POSTDECREMENT:
      return "UNOP_POSTDECREMENT";
    case UNOP_SIZEOF:
      return "UNOP_SIZEOF";
    case UNOP_LOWER:
      return "UNOP_LOWER";
    case UNOP_UPPER:
      return "UNOP_UPPER";
    case UNOP_LENGTH:
      return "UNOP_LENGTH";
    case UNOP_PLUS:
      return "UNOP_PLUS";
    case UNOP_CAP:
      return "UNOP_CAP";
    case UNOP_CHR:
      return "UNOP_CHR";
    case UNOP_ORD:
      return "UNOP_ORD";
    case UNOP_ABS:
      return "UNOP_ABS";
    case UNOP_FLOAT:
      return "UNOP_FLOAT";
    case UNOP_HIGH:
      return "UNOP_HIGH";
    case UNOP_MAX:
      return "UNOP_MAX";
    case UNOP_MIN:
      return "UNOP_MIN";
    case UNOP_ODD:
      return "UNOP_ODD";
    case UNOP_TRUNC:
      return "UNOP_TRUNC";
    case OP_BOOL:
      return "OP_BOOL";
    case OP_M2_STRING:
      return "OP_M2_STRING";
    case STRUCTOP_STRUCT:
      return "STRUCTOP_STRUCT";
    case STRUCTOP_PTR:
      return "STRUCTOP_PTR";
    case OP_THIS:
      return "OP_THIS";
    case OP_OBJC_SELF:
      return "OP_OBJC_SELF";
    case OP_SCOPE:
      return "OP_SCOPE";
    case OP_TYPE:
      return "OP_TYPE";
    case OP_LABELED:
      return "OP_LABELED";
    }
}