#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * ii_owner; int /*<<< orphan*/ * ii_name; } ;
typedef  TYPE_1__ iidesc_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 TYPE_1__* iidesc_dup (TYPE_1__*) ; 
 int /*<<< orphan*/ * xstrdup (char const*) ; 

iidesc_t *
iidesc_dup_rename(iidesc_t *src, char const *name, char const *owner)
{
	iidesc_t *tgt = iidesc_dup(src);
	free(tgt->ii_name);
	free(tgt->ii_owner);

	tgt->ii_name = name ? xstrdup(name) : NULL;
	tgt->ii_owner = owner ? xstrdup(owner) : NULL;

	return (tgt);
}