#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  comment; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ network_mysqld_column_def ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_string_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void network_mysqld_column_def_free(network_mysqld_column_def *column_def) {
	if (!column_def) return;

	g_string_free(column_def->name, TRUE);
	g_string_free(column_def->comment, TRUE);

	g_free(column_def);
}