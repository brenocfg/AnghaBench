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
#define  CCE_ALNUM 150 
#define  CCE_ALPHA 149 
#define  CCE_BLANK 148 
#define  CCE_CNTRL 147 
#define  CCE_DIGIT 146 
#define  CCE_GRAPH 145 
#define  CCE_LOWER 144 
#define  CCE_PRINT 143 
#define  CCE_PUNCT 142 
#define  CCE_SPACE 141 
#define  CCE_UPPER 140 
#define  CCE_XDIGIT 139 
#define  CHAR 138 
 int EOF ; 
#define  EOF_OP 137 
#define  NAME 136 
#define  NUMBER 135 
#define  OPTION_OP 134 
#define  OPT_OUTFILE 133 
#define  OPT_PREFIX 132 
#define  PREVCCL 131 
#define  SCDECL 130 
#define  SECTEND 129 
#define  XSCDECL 128 
 char* _ (char*) ; 
 int eofseen ; 
 int flexscan () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isascii (int) ; 
 int /*<<< orphan*/  isprint (int) ; 
 char* nmstr ; 
 int num_rules ; 
 int /*<<< orphan*/  putc (int,int /*<<< orphan*/ ) ; 
 int sectnum ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  synerr (char*) ; 
 scalar_t__ trace ; 
 int yylval ; 

int     yylex ()
{
	int     toktype;
	static int beglin = false;
	extern char *yytext;

	if (eofseen)
		toktype = EOF;
	else
		toktype = flexscan ();

	if (toktype == EOF || toktype == 0) {
		eofseen = 1;

		if (sectnum == 1) {
			synerr (_("premature EOF"));
			sectnum = 2;
			toktype = SECTEND;
		}

		else
			toktype = 0;
	}

	if (trace) {
		if (beglin) {
			fprintf (stderr, "%d\t", num_rules + 1);
			beglin = 0;
		}

		switch (toktype) {
		case '<':
		case '>':
		case '^':
		case '$':
		case '"':
		case '[':
		case ']':
		case '{':
		case '}':
		case '|':
		case '(':
		case ')':
		case '-':
		case '/':
		case '\\':
		case '?':
		case '.':
		case '*':
		case '+':
		case ',':
			(void) putc (toktype, stderr);
			break;

		case '\n':
			(void) putc ('\n', stderr);

			if (sectnum == 2)
				beglin = 1;

			break;

		case SCDECL:
			fputs ("%s", stderr);
			break;

		case XSCDECL:
			fputs ("%x", stderr);
			break;

		case SECTEND:
			fputs ("%%\n", stderr);

			/* We set beglin to be true so we'll start
			 * writing out numbers as we echo rules.
			 * flexscan() has already assigned sectnum.
			 */
			if (sectnum == 2)
				beglin = 1;

			break;

		case NAME:
			fprintf (stderr, "'%s'", nmstr);
			break;

		case CHAR:
			switch (yylval) {
			case '<':
			case '>':
			case '^':
			case '$':
			case '"':
			case '[':
			case ']':
			case '{':
			case '}':
			case '|':
			case '(':
			case ')':
			case '-':
			case '/':
			case '\\':
			case '?':
			case '.':
			case '*':
			case '+':
			case ',':
				fprintf (stderr, "\\%c", yylval);
				break;

			default:
				if (!isascii (yylval) || !isprint (yylval))
					fprintf (stderr,
						 "\\%.3o",
						 (unsigned int) yylval);
				else
					(void) putc (yylval, stderr);
				break;
			}

			break;

		case NUMBER:
			fprintf (stderr, "%d", yylval);
			break;

		case PREVCCL:
			fprintf (stderr, "[%d]", yylval);
			break;

		case EOF_OP:
			fprintf (stderr, "<<EOF>>");
			break;

		case OPTION_OP:
			fprintf (stderr, "%s ", yytext);
			break;

		case OPT_OUTFILE:
		case OPT_PREFIX:
		case CCE_ALNUM:
		case CCE_ALPHA:
		case CCE_BLANK:
		case CCE_CNTRL:
		case CCE_DIGIT:
		case CCE_GRAPH:
		case CCE_LOWER:
		case CCE_PRINT:
		case CCE_PUNCT:
		case CCE_SPACE:
		case CCE_UPPER:
		case CCE_XDIGIT:
			fprintf (stderr, "%s", yytext);
			break;

		case 0:
			fprintf (stderr, _("End Marker\n"));
			break;

		default:
			fprintf (stderr,
				 _
				 ("*Something Weird* - tok: %d val: %d\n"),
				 toktype, yylval);
			break;
		}
	}

	return toktype;
}