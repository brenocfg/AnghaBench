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
struct see_pre_extension_expr {struct see_pre_extension_expr* next; struct see_pre_extension_expr* avail_occr; struct see_pre_extension_expr* antic_occr; } ;
struct see_occr {struct see_occr* next; struct see_occr* avail_occr; struct see_occr* antic_occr; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct see_pre_extension_expr*) ; 

__attribute__((used)) static void
hash_del_pre_extension (void *p)
{
  struct see_pre_extension_expr *extension = p;
  struct see_occr *curr_occr = extension->antic_occr;
  struct see_occr *next_occr = NULL;

  /*  Free the linked list of the anticipatable occurrences.  */
  while (curr_occr)
    {
      next_occr = curr_occr->next;
      free (curr_occr);
      curr_occr = next_occr;
    }

  /*  Free the linked list of the available occurrences.  */
  curr_occr = extension->avail_occr;
  while (curr_occr)
    {
      next_occr = curr_occr->next;
      free (curr_occr);
      curr_occr = next_occr;
    }

  /* Free the see_pre_extension_expr structure itself.  */
  free (extension);
}