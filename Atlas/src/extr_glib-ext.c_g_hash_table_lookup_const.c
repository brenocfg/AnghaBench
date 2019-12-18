#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gsize ;
typedef  int /*<<< orphan*/  gpointer ;
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_3__ {char* str; int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ GString ;
typedef  int /*<<< orphan*/  GHashTable ;

/* Variables and functions */
 int /*<<< orphan*/  g_hash_table_lookup (int /*<<< orphan*/ *,TYPE_1__*) ; 

gpointer g_hash_table_lookup_const(GHashTable *h, const gchar *name, gsize name_len) {
	GString key;

	key.str = (char *)name; /* we are still const */
	key.len = name_len;

	return g_hash_table_lookup(h, &key);
}