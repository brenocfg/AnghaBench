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
struct TYPE_2__ {int /*<<< orphan*/  backquote; int /*<<< orphan*/  text; int /*<<< orphan*/ * next; } ;
union node {TYPE_1__ narg; int /*<<< orphan*/  type; } ;
struct narg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NARG ; 
 int /*<<< orphan*/  backquotelist ; 
 scalar_t__ stalloc (int) ; 
 int /*<<< orphan*/  wordtext ; 

__attribute__((used)) static union node *
makename(void)
{
	union node *n;

	n = (union node *)stalloc(sizeof (struct narg));
	n->type = NARG;
	n->narg.next = NULL;
	n->narg.text = wordtext;
	n->narg.backquote = backquotelist;
	return n;
}