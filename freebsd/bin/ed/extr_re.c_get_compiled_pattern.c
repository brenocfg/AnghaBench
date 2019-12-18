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
typedef  int /*<<< orphan*/  pattern_t ;

/* Variables and functions */
 char* errmsg ; 
 int /*<<< orphan*/  errno ; 
 char* extract_pattern (char) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 char* ibufp ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ patlock ; 
 int regcomp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regerror (int,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  regfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 

pattern_t *
get_compiled_pattern(void)
{
	static pattern_t *expr = NULL;
	static char error[1024];

	char *exprs;
	char delimiter;
	int n;

	if ((delimiter = *ibufp) == ' ') {
		errmsg = "invalid pattern delimiter";
		return NULL;
	} else if (delimiter == '\n' || *++ibufp == '\n' || *ibufp == delimiter) {
		if (!expr)
			errmsg = "no previous pattern";
		return expr;
	} else if ((exprs = extract_pattern(delimiter)) == NULL)
		return NULL;
	/* buffer alloc'd && not reserved */
	if (expr && !patlock)
		regfree(expr);
	else if ((expr = (pattern_t *) malloc(sizeof(pattern_t))) == NULL) {
		fprintf(stderr, "%s\n", strerror(errno));
		errmsg = "out of memory";
		return NULL;
	}
	patlock = 0;
	if ((n = regcomp(expr, exprs, 0))) {
		regerror(n, expr, error, sizeof error);
		errmsg = error;
		free(expr);
		return expr = NULL;
	}
	return expr;
}