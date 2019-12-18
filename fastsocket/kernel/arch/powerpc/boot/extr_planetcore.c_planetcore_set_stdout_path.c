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
 int /*<<< orphan*/  MAX_PROP_LEN ; 
 int /*<<< orphan*/  PLANETCORE_KEY_SERIAL_PORT ; 
 void* create_node (int /*<<< orphan*/ *,char*) ; 
 void* find_node_by_prop_value_str (int /*<<< orphan*/ *,char*,char const*) ; 
 void* finddevice (char*) ; 
 char* get_path (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* planetcore_get_key (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prop_buf ; 
 int /*<<< orphan*/  setprop_str (void*,char*,char*) ; 

void planetcore_set_stdout_path(const char *table)
{
	char *path;
	const char *label;
	void *node, *chosen;

	label = planetcore_get_key(table, PLANETCORE_KEY_SERIAL_PORT);
	if (!label)
		return;

	node = find_node_by_prop_value_str(NULL, "linux,planetcore-label",
	                                   label);
	if (!node)
		return;

	path = get_path(node, prop_buf, MAX_PROP_LEN);
	if (!path)
		return;

	chosen = finddevice("/chosen");
	if (!chosen)
		chosen = create_node(NULL, "chosen");
	if (!chosen)
		return;

	setprop_str(chosen, "linux,stdout-path", path);
}