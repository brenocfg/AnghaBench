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
 long EOF ; 
 long ERR ; 
 int /*<<< orphan*/  MUST_BE_FIRST () ; 
 int /*<<< orphan*/  SKIP_BLANKS () ; 
 int /*<<< orphan*/  STRTOL (long,int*) ; 
 int /*<<< orphan*/  addr_cnt ; 
 int addr_last ; 
 int current_addr ; 
 char* errmsg ; 
 int /*<<< orphan*/  get_compiled_pattern () ; 
 long get_marked_node_addr (int /*<<< orphan*/ ) ; 
 long get_matching_node_addr (int /*<<< orphan*/ ,int) ; 
 int* ibufp ; 
 int /*<<< orphan*/  isdigit (unsigned char) ; 
 int /*<<< orphan*/  isspace (unsigned char) ; 
 int second_addr ; 

long
next_addr(void)
{
	const char *hd;
	long addr = current_addr;
	long n;
	int first = 1;
	int c;

	SKIP_BLANKS();
	for (hd = ibufp;; first = 0)
		switch (c = *ibufp) {
		case '+':
		case '\t':
		case ' ':
		case '-':
		case '^':
			ibufp++;
			SKIP_BLANKS();
			if (isdigit((unsigned char)*ibufp)) {
				STRTOL(n, ibufp);
				addr += (c == '-' || c == '^') ? -n : n;
			} else if (!isspace((unsigned char)c))
				addr += (c == '-' || c == '^') ? -1 : 1;
			break;
		case '0': case '1': case '2':
		case '3': case '4': case '5':
		case '6': case '7': case '8': case '9':
			MUST_BE_FIRST();
			STRTOL(addr, ibufp);
			break;
		case '.':
		case '$':
			MUST_BE_FIRST();
			ibufp++;
			addr = (c == '.') ? current_addr : addr_last;
			break;
		case '/':
		case '?':
			MUST_BE_FIRST();
			if ((addr = get_matching_node_addr(
			    get_compiled_pattern(), c == '/')) < 0)
				return ERR;
			else if (c == *ibufp)
				ibufp++;
			break;
		case '\'':
			MUST_BE_FIRST();
			ibufp++;
			if ((addr = get_marked_node_addr(*ibufp++)) < 0)
				return ERR;
			break;
		case '%':
		case ',':
		case ';':
			if (first) {
				ibufp++;
				addr_cnt++;
				second_addr = (c == ';') ? current_addr : 1;
				if ((addr = next_addr()) < 0)
					addr = addr_last;
				break;
			}
			/* FALLTHROUGH */
		default:
			if (ibufp == hd)
				return EOF;
			else if (addr < 0 || addr_last < addr) {
				errmsg = "invalid address";
				return ERR;
			} else
				return addr;
		}
	/* NOTREACHED */
}