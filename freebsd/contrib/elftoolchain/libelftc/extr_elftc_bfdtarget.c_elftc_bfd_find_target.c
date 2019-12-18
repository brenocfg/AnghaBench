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
struct TYPE_4__ {scalar_t__ bt_name; } ;
typedef  TYPE_1__ Elftc_Bfd_Target ;

/* Variables and functions */
 TYPE_1__* _libelftc_targets ; 
 int /*<<< orphan*/  strcmp (char const*,scalar_t__) ; 

Elftc_Bfd_Target *
elftc_bfd_find_target(const char *tgt_name)
{
	Elftc_Bfd_Target *tgt;

	for (tgt = _libelftc_targets; tgt->bt_name; tgt++)
		if (!strcmp(tgt_name, tgt->bt_name))
			return (tgt);

	return (NULL);		/* not found */
}