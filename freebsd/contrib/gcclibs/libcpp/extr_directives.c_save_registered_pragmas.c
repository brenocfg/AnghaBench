#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct pragma_entry* space; } ;
struct pragma_entry {TYPE_1__* pragma; TYPE_2__ u; scalar_t__ is_nspace; struct pragma_entry* next; } ;
struct TYPE_3__ {int /*<<< orphan*/  ident; } ;

/* Variables and functions */
 scalar_t__ HT_LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HT_STR (int /*<<< orphan*/ *) ; 
 scalar_t__ xmemdup (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static char **
save_registered_pragmas (struct pragma_entry *pe, char **sd)
{
  for (; pe != NULL; pe = pe->next)
    {
      if (pe->is_nspace)
	sd = save_registered_pragmas (pe->u.space, sd);
      *sd++ = (char *) xmemdup (HT_STR (&pe->pragma->ident),
                                HT_LEN (&pe->pragma->ident),
                                HT_LEN (&pe->pragma->ident) + 1);
    }
  return sd;
}