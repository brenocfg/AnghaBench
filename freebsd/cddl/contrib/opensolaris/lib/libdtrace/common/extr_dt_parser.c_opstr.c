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

/* Variables and functions */
#define  DT_TOK_ADD 187 
#define  DT_TOK_ADDADD 186 
#define  DT_TOK_ADDROF 185 
#define  DT_TOK_ADD_EQ 184 
#define  DT_TOK_AND_EQ 183 
#define  DT_TOK_ASGN 182 
#define  DT_TOK_BAND 181 
#define  DT_TOK_BNEG 180 
#define  DT_TOK_BOR 179 
#define  DT_TOK_COLON 178 
#define  DT_TOK_COMMA 177 
#define  DT_TOK_DEREF 176 
#define  DT_TOK_DIV 175 
#define  DT_TOK_DIV_EQ 174 
#define  DT_TOK_DOT 173 
#define  DT_TOK_ELLIPSIS 172 
#define  DT_TOK_EQU 171 
#define  DT_TOK_GE 170 
#define  DT_TOK_GT 169 
#define  DT_TOK_IDENT 168 
#define  DT_TOK_INEG 167 
#define  DT_TOK_INT 166 
#define  DT_TOK_IPOS 165 
#define  DT_TOK_LAND 164 
#define  DT_TOK_LBRAC 163 
#define  DT_TOK_LE 162 
#define  DT_TOK_LNEG 161 
#define  DT_TOK_LOR 160 
#define  DT_TOK_LPAR 159 
#define  DT_TOK_LSH 158 
#define  DT_TOK_LSH_EQ 157 
#define  DT_TOK_LT 156 
#define  DT_TOK_LXOR 155 
#define  DT_TOK_MOD 154 
#define  DT_TOK_MOD_EQ 153 
#define  DT_TOK_MUL 152 
#define  DT_TOK_MUL_EQ 151 
#define  DT_TOK_NEQ 150 
#define  DT_TOK_OFFSETOF 149 
#define  DT_TOK_OR_EQ 148 
#define  DT_TOK_POSTDEC 147 
#define  DT_TOK_POSTINC 146 
#define  DT_TOK_PREDEC 145 
#define  DT_TOK_PREINC 144 
#define  DT_TOK_PTR 143 
#define  DT_TOK_QUESTION 142 
#define  DT_TOK_RBRAC 141 
#define  DT_TOK_RPAR 140 
#define  DT_TOK_RSH 139 
#define  DT_TOK_RSH_EQ 138 
#define  DT_TOK_SIZEOF 137 
#define  DT_TOK_STRING 136 
#define  DT_TOK_STRINGOF 135 
#define  DT_TOK_SUB 134 
#define  DT_TOK_SUBSUB 133 
#define  DT_TOK_SUB_EQ 132 
#define  DT_TOK_TNAME 131 
#define  DT_TOK_XLATE 130 
#define  DT_TOK_XOR 129 
#define  DT_TOK_XOR_EQ 128 

__attribute__((used)) static const char *
opstr(int op)
{
	switch (op) {
	case DT_TOK_COMMA:	return (",");
	case DT_TOK_ELLIPSIS:	return ("...");
	case DT_TOK_ASGN:	return ("=");
	case DT_TOK_ADD_EQ:	return ("+=");
	case DT_TOK_SUB_EQ:	return ("-=");
	case DT_TOK_MUL_EQ:	return ("*=");
	case DT_TOK_DIV_EQ:	return ("/=");
	case DT_TOK_MOD_EQ:	return ("%=");
	case DT_TOK_AND_EQ:	return ("&=");
	case DT_TOK_XOR_EQ:	return ("^=");
	case DT_TOK_OR_EQ:	return ("|=");
	case DT_TOK_LSH_EQ:	return ("<<=");
	case DT_TOK_RSH_EQ:	return (">>=");
	case DT_TOK_QUESTION:	return ("?");
	case DT_TOK_COLON:	return (":");
	case DT_TOK_LOR:	return ("||");
	case DT_TOK_LXOR:	return ("^^");
	case DT_TOK_LAND:	return ("&&");
	case DT_TOK_BOR:	return ("|");
	case DT_TOK_XOR:	return ("^");
	case DT_TOK_BAND:	return ("&");
	case DT_TOK_EQU:	return ("==");
	case DT_TOK_NEQ:	return ("!=");
	case DT_TOK_LT:		return ("<");
	case DT_TOK_LE:		return ("<=");
	case DT_TOK_GT:		return (">");
	case DT_TOK_GE:		return (">=");
	case DT_TOK_LSH:	return ("<<");
	case DT_TOK_RSH:	return (">>");
	case DT_TOK_ADD:	return ("+");
	case DT_TOK_SUB:	return ("-");
	case DT_TOK_MUL:	return ("*");
	case DT_TOK_DIV:	return ("/");
	case DT_TOK_MOD:	return ("%");
	case DT_TOK_LNEG:	return ("!");
	case DT_TOK_BNEG:	return ("~");
	case DT_TOK_ADDADD:	return ("++");
	case DT_TOK_PREINC:	return ("++");
	case DT_TOK_POSTINC:	return ("++");
	case DT_TOK_SUBSUB:	return ("--");
	case DT_TOK_PREDEC:	return ("--");
	case DT_TOK_POSTDEC:	return ("--");
	case DT_TOK_IPOS:	return ("+");
	case DT_TOK_INEG:	return ("-");
	case DT_TOK_DEREF:	return ("*");
	case DT_TOK_ADDROF:	return ("&");
	case DT_TOK_OFFSETOF:	return ("offsetof");
	case DT_TOK_SIZEOF:	return ("sizeof");
	case DT_TOK_STRINGOF:	return ("stringof");
	case DT_TOK_XLATE:	return ("xlate");
	case DT_TOK_LPAR:	return ("(");
	case DT_TOK_RPAR:	return (")");
	case DT_TOK_LBRAC:	return ("[");
	case DT_TOK_RBRAC:	return ("]");
	case DT_TOK_PTR:	return ("->");
	case DT_TOK_DOT:	return (".");
	case DT_TOK_STRING:	return ("<string>");
	case DT_TOK_IDENT:	return ("<ident>");
	case DT_TOK_TNAME:	return ("<type>");
	case DT_TOK_INT:	return ("<int>");
	default:		return ("<?>");
	}
}