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
typedef  int /*<<< orphan*/ * gpointer ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  GModule ;
typedef  int /*<<< orphan*/  GCallback ;

/* Variables and functions */
 int /*<<< orphan*/ * g_module_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_module_symbol (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static GCallback
self_symbol_lookup(const gchar * symbol_name)
{
    static GModule *module = NULL;
    gpointer symbol = NULL;

    if (!module)
        module = g_module_open(NULL, 0);

    g_module_symbol(module, symbol_name, &symbol);
    return (GCallback) symbol;
}