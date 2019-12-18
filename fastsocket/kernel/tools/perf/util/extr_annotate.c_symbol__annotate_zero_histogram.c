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
struct symbol {int dummy; } ;
struct sym_hist {int dummy; } ;
struct annotation {TYPE_1__* src; } ;
struct TYPE_2__ {int /*<<< orphan*/  sizeof_sym_hist; } ;

/* Variables and functions */
 struct sym_hist* annotation__histogram (struct annotation*,int) ; 
 int /*<<< orphan*/  memset (struct sym_hist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct annotation* symbol__annotation (struct symbol*) ; 

void symbol__annotate_zero_histogram(struct symbol *sym, int evidx)
{
	struct annotation *notes = symbol__annotation(sym);
	struct sym_hist *h = annotation__histogram(notes, evidx);

	memset(h, 0, notes->src->sizeof_sym_hist);
}