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
struct policydb {TYPE_1__* symtab; int /*<<< orphan*/  permissive_map; int /*<<< orphan*/  policycaps; int /*<<< orphan*/  range_tr; int /*<<< orphan*/  te_avtab; } ;
struct TYPE_2__ {int /*<<< orphan*/  table; } ;

/* Variables and functions */
 int SYM_NUM ; 
 int avtab_init (int /*<<< orphan*/ *) ; 
 int cond_policydb_init (struct policydb*) ; 
 int /*<<< orphan*/  ebitmap_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hashtab_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hashtab_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct policydb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rangetr_cmp ; 
 int /*<<< orphan*/  rangetr_hash ; 
 int roles_init (struct policydb*) ; 
 int symtab_init (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * symtab_sizes ; 

__attribute__((used)) static int policydb_init(struct policydb *p)
{
	int i, rc;

	memset(p, 0, sizeof(*p));

	for (i = 0; i < SYM_NUM; i++) {
		rc = symtab_init(&p->symtab[i], symtab_sizes[i]);
		if (rc)
			goto out_free_symtab;
	}

	rc = avtab_init(&p->te_avtab);
	if (rc)
		goto out_free_symtab;

	rc = roles_init(p);
	if (rc)
		goto out_free_symtab;

	rc = cond_policydb_init(p);
	if (rc)
		goto out_free_symtab;

	p->range_tr = hashtab_create(rangetr_hash, rangetr_cmp, 256);
	if (!p->range_tr)
		goto out_free_symtab;

	ebitmap_init(&p->policycaps);
	ebitmap_init(&p->permissive_map);

out:
	return rc;

out_free_symtab:
	for (i = 0; i < SYM_NUM; i++)
		hashtab_destroy(p->symtab[i].table);
	goto out;
}