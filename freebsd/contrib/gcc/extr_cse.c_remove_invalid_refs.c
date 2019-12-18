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
struct table_elt {int /*<<< orphan*/  exp; struct table_elt* next_same_hash; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 unsigned int HASH_SIZE ; 
 int /*<<< orphan*/  REG_P (int /*<<< orphan*/ ) ; 
 scalar_t__ refers_to_regno_p (unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_from_table (struct table_elt*,unsigned int) ; 
 struct table_elt** table ; 

__attribute__((used)) static void
remove_invalid_refs (unsigned int regno)
{
  unsigned int i;
  struct table_elt *p, *next;

  for (i = 0; i < HASH_SIZE; i++)
    for (p = table[i]; p; p = next)
      {
	next = p->next_same_hash;
	if (!REG_P (p->exp)
	    && refers_to_regno_p (regno, regno + 1, p->exp, (rtx *) 0))
	  remove_from_table (p, i);
      }
}