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
struct lang_nocrossrefs {int /*<<< orphan*/ * list; struct lang_nocrossrefs* next; } ;
typedef  int /*<<< orphan*/  lang_nocrossref_type ;
struct TYPE_2__ {int /*<<< orphan*/  notice_all; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__ link_info ; 
 struct lang_nocrossrefs* nocrossref_list ; 
 struct lang_nocrossrefs* xmalloc (int) ; 

void
lang_add_nocrossref (lang_nocrossref_type *l)
{
  struct lang_nocrossrefs *n;

  n = xmalloc (sizeof *n);
  n->next = nocrossref_list;
  n->list = l;
  nocrossref_list = n;

  /* Set notice_all so that we get informed about all symbols.  */
  link_info.notice_all = TRUE;
}