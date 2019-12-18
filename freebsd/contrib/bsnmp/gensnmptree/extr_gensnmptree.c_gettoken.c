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
#define  TOK_ACCESS 138 
#define  TOK_BITS 137 
#define  TOK_DEFTYPE 136 
#define  TOK_ENUM 135 
#define  TOK_EOF 134 
#define  TOK_FILENAME 133 
#define  TOK_INCLUDE 132 
#define  TOK_NUM 131 
#define  TOK_STR 130 
#define  TOK_TYPE 129 
#define  TOK_TYPEDEF 128 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int gettoken_internal () ; 
 int /*<<< orphan*/  isprint (int) ; 
 int /*<<< orphan*/  stderr ; 
 char* str ; 
 int val ; 

__attribute__((used)) static int
gettoken(void)
{
	int tok = gettoken_internal();

	if (debug) {
		switch (tok) {

		  case TOK_EOF:
			fprintf(stderr, "EOF ");
			break;

		  case TOK_NUM:
			fprintf(stderr, "NUM(%lu) ", val);
			break;

		  case TOK_STR:
			fprintf(stderr, "STR(%s) ", str);
			break;

		  case TOK_ACCESS:
			fprintf(stderr, "ACCESS(%lu) ", val);
			break;

		  case TOK_TYPE:
			fprintf(stderr, "TYPE(%lu) ", val);
			break;

		  case TOK_ENUM:
			fprintf(stderr, "ENUM ");
			break;

		  case TOK_BITS:
			fprintf(stderr, "BITS ");
			break;

		  case TOK_TYPEDEF:
			fprintf(stderr, "TYPEDEF ");
			break;

		  case TOK_DEFTYPE:
			fprintf(stderr, "DEFTYPE(%s,%lu) ", str, val);
			break;

		  case TOK_INCLUDE:
			fprintf(stderr, "INCLUDE ");
			break;

		  case TOK_FILENAME:
			fprintf(stderr, "FILENAME ");
			break;

		  default:
			if (tok < TOK_EOF) {
				if (isprint(tok))
					fprintf(stderr, "'%c' ", tok);
				else if (tok == '\n')
					fprintf(stderr, "\n");
				else
					fprintf(stderr, "%02x ", tok);
			} else
				abort();
			break;
		}
	}
	return (tok);
}