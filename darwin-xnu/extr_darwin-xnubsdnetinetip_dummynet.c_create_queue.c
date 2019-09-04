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
struct dn_flow_set {int rq_elements; int rq_size; struct dn_flow_queue** rq; } ;
struct dn_flow_queue {int hash_slot; scalar_t__ F; scalar_t__ S; struct dn_flow_queue* next; struct dn_flow_set* fs; } ;

/* Variables and functions */
 int M_DONTWAIT ; 
 int /*<<< orphan*/  M_DUMMYNET ; 
 int M_ZERO ; 
 struct dn_flow_queue* _MALLOC (int,int /*<<< orphan*/ ,int) ; 
 int dn_max_ratio ; 
 scalar_t__ expire_queues (struct dn_flow_set*) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static struct dn_flow_queue *
create_queue(struct dn_flow_set *fs, int i)
{
    struct dn_flow_queue *q ;

    if (fs->rq_elements > fs->rq_size * dn_max_ratio &&
	    expire_queues(fs) == 0) {
	/*
	 * No way to get room, use or create overflow queue.
	 */
	i = fs->rq_size ;
	if ( fs->rq[i] != NULL )
	    return fs->rq[i] ;
    }
    q = _MALLOC(sizeof(*q), M_DUMMYNET, M_DONTWAIT | M_ZERO);
    if (q == NULL) {
	printf("dummynet: sorry, cannot allocate queue for new flow\n");
	return NULL ;
    }
    q->fs = fs ;
    q->hash_slot = i ;
    q->next = fs->rq[i] ;
    q->S = q->F + 1;   /* hack - mark timestamp as invalid */
    fs->rq[i] = q ;
    fs->rq_elements++ ;
    return q ;
}