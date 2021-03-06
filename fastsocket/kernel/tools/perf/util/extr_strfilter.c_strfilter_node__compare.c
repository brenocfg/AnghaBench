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
struct strfilter_node {int* p; struct strfilter_node* r; struct strfilter_node* l; } ;

/* Variables and functions */
 int strglobmatch (char const*,int*) ; 

__attribute__((used)) static bool strfilter_node__compare(struct strfilter_node *self,
				    const char *str)
{
	if (!self || !self->p)
		return false;

	switch (*self->p) {
	case '|':	/* OR */
		return strfilter_node__compare(self->l, str) ||
			strfilter_node__compare(self->r, str);
	case '&':	/* AND */
		return strfilter_node__compare(self->l, str) &&
			strfilter_node__compare(self->r, str);
	case '!':	/* NOT */
		return !strfilter_node__compare(self->r, str);
	default:
		return strglobmatch(str, self->p);
	}
}