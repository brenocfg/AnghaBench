#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  table; } ;
struct common_datum {TYPE_1__ permissions; } ;

/* Variables and functions */
 int /*<<< orphan*/  hashtab_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashtab_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  perm_destroy ; 

__attribute__((used)) static int common_destroy(void *key, void *datum, void *p)
{
	struct common_datum *comdatum;

	kfree(key);
	comdatum = datum;
	hashtab_map(comdatum->permissions.table, perm_destroy, NULL);
	hashtab_destroy(comdatum->permissions.table);
	kfree(datum);
	return 0;
}