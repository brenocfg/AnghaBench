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
struct timeval {scalar_t__ tv_sec; } ;
struct dn_flow_set {int rq_elements; scalar_t__ last_expired; int rq_size; struct dn_flow_queue** rq; } ;
struct dn_flow_queue {scalar_t__ S; scalar_t__ F; struct dn_flow_queue* next; int /*<<< orphan*/ * head; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (struct dn_flow_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_DUMMYNET ; 
 int /*<<< orphan*/  getmicrotime (struct timeval*) ; 

__attribute__((used)) static int
expire_queues(struct dn_flow_set *fs)
{
    struct dn_flow_queue *q, *prev ;
    int i, initial_elements = fs->rq_elements ;
	struct timeval timenow;

	/* reviewed for getmicrotime usage */
	getmicrotime(&timenow);

    if (fs->last_expired == timenow.tv_sec)
	return 0 ;
    fs->last_expired = timenow.tv_sec ;
    for (i = 0 ; i <= fs->rq_size ; i++) /* last one is overflow */
	for (prev=NULL, q = fs->rq[i] ; q != NULL ; )
	    if (q->head != NULL || q->S != q->F+1) {
  		prev = q ;
  	        q = q->next ;
  	    } else { /* entry is idle, expire it */
		struct dn_flow_queue *old_q = q ;

		if (prev != NULL)
		    prev->next = q = q->next ;
		else
		    fs->rq[i] = q = q->next ;
		fs->rq_elements-- ;
		FREE(old_q, M_DUMMYNET);
	    }
    return initial_elements - fs->rq_elements ;
}