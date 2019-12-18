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
struct symbol {int end; int start; scalar_t__ binding; int /*<<< orphan*/  name; } ;
typedef  int s64 ;

/* Variables and functions */
 scalar_t__ STB_GLOBAL ; 
 scalar_t__ STB_WEAK ; 
 int SYMBOL_A ; 
 int SYMBOL_B ; 
 int prefix_underscores_count (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int choose_best_symbol(struct symbol *syma, struct symbol *symb)
{
	s64 a;
	s64 b;

	/* Prefer a symbol with non zero length */
	a = syma->end - syma->start;
	b = symb->end - symb->start;
	if ((b == 0) && (a > 0))
		return SYMBOL_A;
	else if ((a == 0) && (b > 0))
		return SYMBOL_B;

	/* Prefer a non weak symbol over a weak one */
	a = syma->binding == STB_WEAK;
	b = symb->binding == STB_WEAK;
	if (b && !a)
		return SYMBOL_A;
	if (a && !b)
		return SYMBOL_B;

	/* Prefer a global symbol over a non global one */
	a = syma->binding == STB_GLOBAL;
	b = symb->binding == STB_GLOBAL;
	if (a && !b)
		return SYMBOL_A;
	if (b && !a)
		return SYMBOL_B;

	/* Prefer a symbol with less underscores */
	a = prefix_underscores_count(syma->name);
	b = prefix_underscores_count(symb->name);
	if (b > a)
		return SYMBOL_A;
	else if (a > b)
		return SYMBOL_B;

	/* If all else fails, choose the symbol with the longest name */
	if (strlen(syma->name) >= strlen(symb->name))
		return SYMBOL_A;
	else
		return SYMBOL_B;
}