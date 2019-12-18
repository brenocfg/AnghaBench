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
typedef  int /*<<< orphan*/  s ;
typedef  int /*<<< orphan*/  prompt ;
typedef  int UWORD ;
typedef  int /*<<< orphan*/  UBYTE ;
typedef  int SWORD ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  MEMORY_dPutByte (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEMORY_dPutWord (int,int) ; 
 int /*<<< orphan*/  Util_strupper (char*) ; 
 char** instr6502 ; 
 int /*<<< orphan*/  parse_hex (char*,int*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  safe_gets (char*,int,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static UWORD assembler(UWORD addr)
{
	printf("Simple assembler (enter empty line to exit)\n");
	for (;;) {
		char s[128];  /* input string */
		char c[128];  /* converted input */
		char *sp;     /* input pointer */
		char *cp;     /* converted input pointer */
		char *vp;     /* value pointer (the value is stored in s) */
		char *tp;     /* type pointer (points at type character '0', '1' or '2' in converted input) */
		int i;
		int isa;      /* the operand is "A" */
		UWORD value = 0;

		char prompt[7];
		snprintf(prompt, sizeof(prompt), "%04X: ", (int) addr);
		safe_gets(s, sizeof(s), prompt);
		if (s[0] == '\0')
			return addr;

		Util_strupper(s);

		sp = s;
		cp = c;
		/* copy first three characters */
		for (i = 0; i < 3 && *sp != '\0'; i++)
			*cp++ = *sp++;
		/* insert space before operands */
		*cp++ = ' ';

		tp = NULL;
		isa = FALSE;

		/* convert input to format of instr6502[] table */
		while (*sp != '\0') {
			switch (*sp) {
			case ' ':
			case '\t':
			case '$':
			case '@':
				sp++;
				break;
			case '#':
			case '(':
			case ')':
			case ',':
				isa = FALSE;
				*cp++ = *sp++;
				break;
			default:
				if (tp != NULL) {
					if (*sp == 'X' || *sp == 'Y') {
						*cp++ = *sp++;
						break;
					}
					goto invalid_instr;
				}
				vp = s;
				do
					*vp++ = *sp++;
				while (strchr(" \t$@#(),", *sp) == NULL && *sp != '\0');
				/* If *sp=='\0', strchr() should return non-NULL,
				   but we do an extra check to be on safe side. */
				*vp++ = '\0';
				tp = cp++;
				*tp = '0';
				isa = (s[0] == 'A' && s[1] == '\0');
				break;
			}
		}
		if (cp[-1] == ' ')
			cp--;    /* no arguments (e.g. NOP or ASL @) */
		*cp = '\0';

		/* if there's an operand, get its value */
		if (tp != NULL && !parse_hex(s, &value)) {
			printf("Invalid operand!\n");
			continue;
		}

		for (;;) {
			/* search table for instruction */
			for (i = 0; i < 256; i++) {
				if (strcmp(instr6502[i], c) == 0) {
					if (tp == NULL) {
						MEMORY_dPutByte(addr, (UBYTE) i);
						addr++;
					}
					else if (*tp == '0') {
						value -= (addr + 2);
						if ((SWORD) value < -128 || (SWORD) value > 127)
							printf("Branch out of range!\n");
						else {
							MEMORY_dPutByte(addr, (UBYTE) i);
							addr++;
							MEMORY_dPutByte(addr, (UBYTE) value);
							addr++;
						}
					}
					else if (*tp == '1') {
						c[3] = '\0';
						if (isa && (strcmp(c, "ASL") == 0 || strcmp(c, "LSR") == 0 ||
						            strcmp(c, "ROL") == 0 || strcmp(c, "ROR") == 0)) {
							printf("\"%s A\" is ambiguous.\n"
							       "Use \"%s\" for accumulator mode or \"%s 0A\" for zeropage mode.\n", c, c, c);
						}
						else {
							MEMORY_dPutByte(addr, (UBYTE) i);
							addr++;
							MEMORY_dPutByte(addr, (UBYTE) value);
							addr++;
						}
					}
					else { /* *tp == '2' */
						MEMORY_dPutByte(addr, (UBYTE) i);
						addr++;
						MEMORY_dPutWord(addr, value);
						addr += 2;
					}
					goto next_instr;
				}
			}
			/* not found */
			if (tp == NULL || *tp == '2')
				break;
			if (++*tp == '1' && value > 0xff)
				*tp = '2';
		}
	invalid_instr:
		printf("Invalid instruction!\n");
	next_instr:
		;
	}
}