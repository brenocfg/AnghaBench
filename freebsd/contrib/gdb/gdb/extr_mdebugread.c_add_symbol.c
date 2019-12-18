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
struct symbol {int dummy; } ;
struct block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_DICT (struct block*) ; 
 int /*<<< orphan*/  dict_add_symbol (int /*<<< orphan*/ ,struct symbol*) ; 

__attribute__((used)) static void
add_symbol (struct symbol *s, struct block *b)
{
  dict_add_symbol (BLOCK_DICT (b), s);
}