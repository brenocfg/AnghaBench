#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int t_id; int /*<<< orphan*/  t_flags; int /*<<< orphan*/  t_size; int /*<<< orphan*/  t_type; int /*<<< orphan*/ * t_name; } ;
typedef  TYPE_1__ tdesc_t ;

/* Variables and functions */
 TYPE_1__* xcalloc (int) ; 
 int /*<<< orphan*/ * xstrdup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static tdesc_t *
conjure_template(tdesc_t *old, int newselfid)
{
	tdesc_t *new = xcalloc(sizeof (tdesc_t));

	new->t_name = old->t_name ? xstrdup(old->t_name) : NULL;
	new->t_type = old->t_type;
	new->t_size = old->t_size;
	new->t_id = newselfid;
	new->t_flags = old->t_flags;

	return (new);
}