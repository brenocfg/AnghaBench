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
 char ToUpper (char) ; 

char *CharToNetBiosStr(char c)
{
	c = ToUpper(c);

	switch (c)
	{
	case '\0':	return "AA";
	case 'A':	return "EB";
	case 'B':	return "EC";
	case 'C':	return "ED";
	case 'D':	return "EE";
	case 'E':	return "EF";
	case 'F':	return "EG";
	case 'G':	return "EH";
	case 'H':	return "EI";
	case 'I':	return "EJ";
	case 'J':	return "EK";
	case 'K':	return "EL";
	case 'L':	return "EM";
	case 'M':	return "EN";
	case 'N':	return "EO";
	case 'O':	return "EP";
	case 'P':	return "FA";
	case 'Q':	return "FB";
	case 'R':	return "FC";
	case 'S':	return "FD";
	case 'T':	return "FE";
	case 'U':	return "FF";
	case 'V':	return "FG";
	case 'W':	return "FH";
	case 'X':	return "FI";
	case 'Y':	return "FJ";
	case 'Z':	return "FK";
	case '0':	return "DA";
	case '1':	return "DB";
	case '2':	return "DC";
	case '3':	return "DD";
	case '4':	return "DE";
	case '5':	return "DF";
	case '6':	return "DG";
	case '7':	return "DH";
	case '8':	return "DI";
	case '9':	return "DJ";
	case ' ':	return "CA";
	case '!':	return "CB";
	case '\"':	return "CC";
	case '#':	return "CD";
	case '$':	return "CE";
	case '%':	return "CF";
	case '&':	return "CG";
	case '\'':	return "CH";
	case '(':	return "CI";
	case ')':	return "CJ";
	case '*':	return "CK";
	case '+':	return "CL";
	case ',':	return "CM";
	case '-':	return "CN";
	case '.':	return "CO";
	case '=':	return "DN";
	case ':':	return "DK";
	case ';':	return "DL";
	case '@':	return "EA";
	case '^':	return "FO";
	case '_':	return "FP";
	case '{':	return "HL";
	case '}':	return "HN";
	case '~':	return "HO";
	}

	return "CA";
}