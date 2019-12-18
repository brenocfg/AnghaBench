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
struct hash_table {struct expr** table; int /*<<< orphan*/  size; } ;
struct expr {struct expr* next_same_hash; int /*<<< orphan*/  expr; } ;

/* Variables and functions */
 unsigned int REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_DEST (int /*<<< orphan*/ ) ; 
 unsigned int hash_set (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct expr *
lookup_set (unsigned int regno, struct hash_table *table)
{
  unsigned int hash = hash_set (regno, table->size);
  struct expr *expr;

  expr = table->table[hash];

  while (expr && REGNO (SET_DEST (expr->expr)) != regno)
    expr = expr->next_same_hash;

  return expr;
}