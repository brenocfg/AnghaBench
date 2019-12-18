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
struct nfs_seqid_counter {int dummy; } ;
struct nfs_seqid {int /*<<< orphan*/  list; struct nfs_seqid_counter* sequence; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct nfs_seqid* kmalloc (int,int /*<<< orphan*/ ) ; 

struct nfs_seqid *nfs_alloc_seqid(struct nfs_seqid_counter *counter, gfp_t gfp_mask)
{
	struct nfs_seqid *new;

	new = kmalloc(sizeof(*new), gfp_mask);
	if (new != NULL) {
		new->sequence = counter;
		INIT_LIST_HEAD(&new->list);
	}
	return new;
}