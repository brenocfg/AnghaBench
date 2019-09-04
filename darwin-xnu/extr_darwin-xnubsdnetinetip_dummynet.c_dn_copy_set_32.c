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
typedef  void* user32_addr_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct dn_flow_set {int rq_size; int rq_elements; struct dn_flow_queue** rq; } ;
struct dn_flow_queue_32 {void* fs; void* tail; void* head; void* next; } ;
struct dn_flow_queue {int hash_slot; struct dn_flow_set* fs; struct dn_flow_queue* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 scalar_t__ VM_KERNEL_ADDRPERM (struct dn_flow_set*) ; 
 int /*<<< orphan*/  cp_queue_to_32_user (struct dn_flow_queue*,struct dn_flow_queue_32*) ; 
 int /*<<< orphan*/  dn_mutex ; 
 int /*<<< orphan*/  printf (char*,int,int,...) ; 

__attribute__((used)) static
char* dn_copy_set_32(struct dn_flow_set *set, char *bp)
{
    int i, copied = 0 ;
    struct dn_flow_queue *q;
	struct dn_flow_queue_32 *qp = (struct dn_flow_queue_32 *)bp;

	LCK_MTX_ASSERT(dn_mutex, LCK_MTX_ASSERT_OWNED);

    for (i = 0 ; i <= set->rq_size ; i++)
		for (q = set->rq[i] ; q ; q = q->next, qp++ ) {
			if (q->hash_slot != i)
				printf("dummynet: ++ at %d: wrong slot (have %d, "
					   "should be %d)\n", copied, q->hash_slot, i);
			if (q->fs != set)
				printf("dummynet: ++ at %d: wrong fs ptr "
				    "(have 0x%llx, should be 0x%llx)\n", i,
				    (uint64_t)VM_KERNEL_ADDRPERM(q->fs),
				    (uint64_t)VM_KERNEL_ADDRPERM(set));
			copied++ ;
			cp_queue_to_32_user( q, qp );
			/* cleanup pointers */
			qp->next = (user32_addr_t)0 ;
			qp->head = qp->tail = (user32_addr_t)0 ;
			qp->fs = (user32_addr_t)0 ;
		}
    if (copied != set->rq_elements)
		printf("dummynet: ++ wrong count, have %d should be %d\n",
			   copied, set->rq_elements);
    return (char *)qp ;
}