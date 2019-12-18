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
typedef  scalar_t__ gint ;
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  GTree ;
typedef  int /*<<< orphan*/  GCompareFunc ;

/* Variables and functions */
 int /*<<< orphan*/  GINT_TO_POINTER (scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ g_ascii_strcasecmp ; 
 int /*<<< orphan*/  g_tree_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_tree_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_tree_insert (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_tree_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ sql_token_get_last_id () ; 
 int sql_token_get_name (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ strncmp (int,char*,int) ; 
 int /*<<< orphan*/  trav ; 

int main() {
	GTree *tokens;
	gboolean is_first = TRUE;
	gint i;

	tokens = g_tree_new((GCompareFunc)g_ascii_strcasecmp);

	for (i = 0; i < sql_token_get_last_id(); i++) {
		/** only tokens with TK_SQL_* are keyworks */
		if (0 != strncmp(sql_token_get_name(i, NULL), "TK_SQL_", sizeof("TK_SQL_") - 1)) continue;

		g_tree_insert(tokens, (sql_token_get_name(i, NULL) + sizeof("TK_SQL_") - 1), GINT_TO_POINTER(i));
	}

	/* traverse the tree and output all keywords in a sorted way */
	printf("static int sql_keywords[] = {");
	g_tree_foreach(tokens, trav, &is_first);
	printf("\n};\n");

	printf("int *sql_keywords_get() { return sql_keywords; }\n");
	printf("int sql_keywords_get_count() { return sizeof(sql_keywords) / sizeof(sql_keywords[0]); }\n");

	g_tree_destroy(tokens);

	return 0;
}