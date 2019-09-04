#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int numleafsh; int numleafsv; scalar_t__ numnodes; TYPE_2__* nodes; } ;
typedef  TYPE_1__ opj_tgt_tree_t ;
struct TYPE_7__ {struct TYPE_7__* parent; } ;
typedef  TYPE_2__ opj_tgt_node_t ;

/* Variables and functions */
 scalar_t__ opj_calloc (scalar_t__,int) ; 
 int /*<<< orphan*/  opj_free (TYPE_1__*) ; 
 scalar_t__ opj_malloc (int) ; 
 int /*<<< orphan*/  tgt_reset (TYPE_1__*) ; 

opj_tgt_tree_t *tgt_create(int numleafsh, int numleafsv) {
	int nplh[32];
	int nplv[32];
	opj_tgt_node_t *node = NULL;
	opj_tgt_node_t *parentnode = NULL;
	opj_tgt_node_t *parentnode0 = NULL;
	opj_tgt_tree_t *tree = NULL;
	int i, j, k;
	int numlvls;
	int n;

	tree = (opj_tgt_tree_t *) opj_malloc(sizeof(opj_tgt_tree_t));
	if(!tree) return NULL;
	tree->numleafsh = numleafsh;
	tree->numleafsv = numleafsv;

	numlvls = 0;
	nplh[0] = numleafsh;
	nplv[0] = numleafsv;
	tree->numnodes = 0;
	do {
		n = nplh[numlvls] * nplv[numlvls];
		nplh[numlvls + 1] = (nplh[numlvls] + 1) / 2;
		nplv[numlvls + 1] = (nplv[numlvls] + 1) / 2;
		tree->numnodes += n;
		++numlvls;
	} while (n > 1);
	
	/* ADD */
	if (tree->numnodes == 0) {
		opj_free(tree);
		return NULL;
	}

	tree->nodes = (opj_tgt_node_t*) opj_calloc(tree->numnodes, sizeof(opj_tgt_node_t));
	if(!tree->nodes) {
		opj_free(tree);
		return NULL;
	}

	node = tree->nodes;
	parentnode = &tree->nodes[tree->numleafsh * tree->numleafsv];
	parentnode0 = parentnode;
	
	for (i = 0; i < numlvls - 1; ++i) {
		for (j = 0; j < nplv[i]; ++j) {
			k = nplh[i];
			while (--k >= 0) {
				node->parent = parentnode;
				++node;
				if (--k >= 0) {
					node->parent = parentnode;
					++node;
				}
				++parentnode;
			}
			if ((j & 1) || j == nplv[i] - 1) {
				parentnode0 = parentnode;
			} else {
				parentnode = parentnode0;
				parentnode0 += nplh[i];
			}
		}
	}
	node->parent = 0;
	
	tgt_reset(tree);
	
	return tree;
}