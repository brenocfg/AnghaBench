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
typedef  int /*<<< orphan*/  gsize ;
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  GString ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  S (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_free (char*) ; 
 scalar_t__ g_string_equal (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 char* g_utf8_casefold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strleq (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

gboolean g_string_equal_ci(const GString *a, const GString *b) {
	char *a_ci, *b_ci;
	gsize a_ci_len, b_ci_len;
	gboolean is_equal = FALSE;

	if (g_string_equal(a, b)) return TRUE;

	a_ci = g_utf8_casefold(S(a));
	a_ci_len = strlen(a_ci);
	
	b_ci = g_utf8_casefold(S(b));
	b_ci_len = strlen(b_ci);

	is_equal = strleq(a_ci, a_ci_len, b_ci, b_ci_len);

	g_free(a_ci);
	g_free(b_ci);

	return is_equal;
}