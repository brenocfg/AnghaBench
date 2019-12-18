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
struct fib6_walker_t {int state; int (* func ) (struct fib6_walker_t*) ;struct fib6_node* node; int /*<<< orphan*/  leaf; struct fib6_node* root; scalar_t__ prune; } ;
struct fib6_node {int fn_flags; int /*<<< orphan*/  leaf; struct fib6_node* right; struct fib6_node* left; struct fib6_node* parent; } ;

/* Variables and functions */
 struct fib6_node* FIB6_SUBTREE (struct fib6_node*) ; 
#define  FWS_C 132 
 void* FWS_INIT ; 
#define  FWS_L 131 
#define  FWS_R 130 
#define  FWS_S 129 
#define  FWS_U 128 
 int RTN_ROOT ; 
 int RTN_RTINFO ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int stub1 (struct fib6_walker_t*) ; 

__attribute__((used)) static int fib6_walk_continue(struct fib6_walker_t *w)
{
	struct fib6_node *fn, *pn;

	for (;;) {
		fn = w->node;
		if (fn == NULL)
			return 0;

		if (w->prune && fn != w->root &&
		    fn->fn_flags&RTN_RTINFO && w->state < FWS_C) {
			w->state = FWS_C;
			w->leaf = fn->leaf;
		}
		switch (w->state) {
#ifdef CONFIG_IPV6_SUBTREES
		case FWS_S:
			if (FIB6_SUBTREE(fn)) {
				w->node = FIB6_SUBTREE(fn);
				continue;
			}
			w->state = FWS_L;
#endif
		case FWS_L:
			if (fn->left) {
				w->node = fn->left;
				w->state = FWS_INIT;
				continue;
			}
			w->state = FWS_R;
		case FWS_R:
			if (fn->right) {
				w->node = fn->right;
				w->state = FWS_INIT;
				continue;
			}
			w->state = FWS_C;
			w->leaf = fn->leaf;
		case FWS_C:
			if (w->leaf && fn->fn_flags&RTN_RTINFO) {
				int err = w->func(w);
				if (err)
					return err;
				continue;
			}
			w->state = FWS_U;
		case FWS_U:
			if (fn == w->root)
				return 0;
			pn = fn->parent;
			w->node = pn;
#ifdef CONFIG_IPV6_SUBTREES
			if (FIB6_SUBTREE(pn) == fn) {
				WARN_ON(!(fn->fn_flags & RTN_ROOT));
				w->state = FWS_L;
				continue;
			}
#endif
			if (pn->left == fn) {
				w->state = FWS_R;
				continue;
			}
			if (pn->right == fn) {
				w->state = FWS_C;
				w->leaf = w->node->leaf;
				continue;
			}
#if RT6_DEBUG >= 2
			WARN_ON(1);
#endif
		}
	}
}