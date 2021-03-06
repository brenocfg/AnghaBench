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
struct symbol_cache {struct symbol_cache* symbol; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct symbol_cache*) ; 

__attribute__((used)) static void free_symbol_cache(struct symbol_cache *sc)
{
	kfree(sc->symbol);
	kfree(sc);
}