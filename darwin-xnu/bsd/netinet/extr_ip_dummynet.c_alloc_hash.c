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
struct dn_flow_set {int flags_fs; int rq_size; scalar_t__ rq_elements; int /*<<< orphan*/ * rq; } ;
struct dn_flow_queue {int dummy; } ;

/* Variables and functions */
 int DN_HAVE_FLOW_MASK ; 
 int DN_MAX_HASH_SIZE ; 
 int ENOSPC ; 
 int M_DONTWAIT ; 
 int /*<<< orphan*/  M_DUMMYNET ; 
 int M_ZERO ; 
 int /*<<< orphan*/ * _MALLOC (int,int /*<<< orphan*/ ,int) ; 
 int dn_hash_size ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
alloc_hash(struct dn_flow_set *x, struct dn_flow_set *pfs)
{
    if (x->flags_fs & DN_HAVE_FLOW_MASK) {     /* allocate some slots */
	int l = pfs->rq_size;

	if (l == 0)
	    l = dn_hash_size;
	if (l < 4)
	    l = 4;
	else if (l > DN_MAX_HASH_SIZE)
	    l = DN_MAX_HASH_SIZE;
	x->rq_size = l;
    } else                  /* one is enough for null mask */
	x->rq_size = 1;
    x->rq = _MALLOC((1 + x->rq_size) * sizeof(struct dn_flow_queue *),
	    M_DUMMYNET, M_DONTWAIT | M_ZERO);
    if (x->rq == NULL) {
	printf("dummynet: sorry, cannot allocate queue\n");
	return ENOSPC;
    }
    x->rq_elements = 0;
    return 0 ;
}