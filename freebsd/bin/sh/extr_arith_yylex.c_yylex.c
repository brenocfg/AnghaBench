#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* name; int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARITH_ADD ; 
 int /*<<< orphan*/  ARITH_AND ; 
 int /*<<< orphan*/  ARITH_ASS ; 
 int ARITH_BAD ; 
 int /*<<< orphan*/  ARITH_BAND ; 
 int /*<<< orphan*/  ARITH_BNOT ; 
 int /*<<< orphan*/  ARITH_BOR ; 
 int /*<<< orphan*/  ARITH_BXOR ; 
 int /*<<< orphan*/  ARITH_COLON ; 
 int /*<<< orphan*/  ARITH_DIV ; 
 int /*<<< orphan*/  ARITH_GE ; 
 int /*<<< orphan*/  ARITH_GT ; 
 int /*<<< orphan*/  ARITH_LE ; 
 int /*<<< orphan*/  ARITH_LPAREN ; 
 int /*<<< orphan*/  ARITH_LSHIFT ; 
 int /*<<< orphan*/  ARITH_LT ; 
 int /*<<< orphan*/  ARITH_MUL ; 
 int /*<<< orphan*/  ARITH_NE ; 
 int /*<<< orphan*/  ARITH_NOT ; 
 int ARITH_NUM ; 
 int /*<<< orphan*/  ARITH_OR ; 
 int /*<<< orphan*/  ARITH_QMARK ; 
 int /*<<< orphan*/  ARITH_REM ; 
 int /*<<< orphan*/  ARITH_RPAREN ; 
 int /*<<< orphan*/  ARITH_RSHIFT ; 
 int /*<<< orphan*/  ARITH_SUB ; 
 int ARITH_VAR ; 
 char const* arith_buf ; 
 int /*<<< orphan*/  is_in_name (char const) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* stalloc (int) ; 
 int /*<<< orphan*/  strtoarith_t (char const*,char**) ; 
 TYPE_1__ yylval ; 

int
yylex(void)
{
	int value;
	const char *buf = arith_buf;
	char *end;
	const char *p;

	for (;;) {
		value = *buf;
		switch (value) {
		case ' ':
		case '\t':
		case '\n':
			buf++;
			continue;
		default:
			return ARITH_BAD;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			yylval.val = strtoarith_t(buf, &end);
			arith_buf = end;
			return ARITH_NUM;
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z':
			p = buf;
			while (buf++, is_in_name(*buf))
				;
			yylval.name = stalloc(buf - p + 1);
			memcpy(yylval.name, p, buf - p);
			yylval.name[buf - p] = '\0';
			value = ARITH_VAR;
			goto out;
		case '=':
			value += ARITH_ASS - '=';
checkeq:
			buf++;
checkeqcur:
			if (*buf != '=')
				goto out;
			value += 11;
			break;
		case '>':
			switch (*++buf) {
			case '=':
				value += ARITH_GE - '>';
				break;
			case '>':
				value += ARITH_RSHIFT - '>';
				goto checkeq;
			default:
				value += ARITH_GT - '>';
				goto out;
			}
			break;
		case '<':
			switch (*++buf) {
			case '=':
				value += ARITH_LE - '<';
				break;
			case '<':
				value += ARITH_LSHIFT - '<';
				goto checkeq;
			default:
				value += ARITH_LT - '<';
				goto out;
			}
			break;
		case '|':
			if (*++buf != '|') {
				value += ARITH_BOR - '|';
				goto checkeqcur;
			}
			value += ARITH_OR - '|';
			break;
		case '&':
			if (*++buf != '&') {
				value += ARITH_BAND - '&';
				goto checkeqcur;
			}
			value += ARITH_AND - '&';
			break;
		case '!':
			if (*++buf != '=') {
				value += ARITH_NOT - '!';
				goto out;
			}
			value += ARITH_NE - '!';
			break;
		case 0:
			goto out;
		case '(':
			value += ARITH_LPAREN - '(';
			break;
		case ')':
			value += ARITH_RPAREN - ')';
			break;
		case '*':
			value += ARITH_MUL - '*';
			goto checkeq;
		case '/':
			value += ARITH_DIV - '/';
			goto checkeq;
		case '%':
			value += ARITH_REM - '%';
			goto checkeq;
		case '+':
			if (buf[1] == '+')
				return ARITH_BAD;
			value += ARITH_ADD - '+';
			goto checkeq;
		case '-':
			if (buf[1] == '-')
				return ARITH_BAD;
			value += ARITH_SUB - '-';
			goto checkeq;
		case '~':
			value += ARITH_BNOT - '~';
			break;
		case '^':
			value += ARITH_BXOR - '^';
			goto checkeq;
		case '?':
			value += ARITH_QMARK - '?';
			break;
		case ':':
			value += ARITH_COLON - ':';
			break;
		}
		break;
	}

	buf++;
out:
	arith_buf = buf;
	return value;
}