#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int* __u6_addr32; } ;
struct TYPE_8__ {TYPE_2__ __u6_addr; } ;
struct ip_flow_id {int dst_port; int src_port; int proto; scalar_t__ flags; int flow_id6; int dst_ip; int src_ip; TYPE_3__ src_ip6; TYPE_3__ dst_ip6; } ;
struct TYPE_6__ {int dst_port; int src_port; int proto; int flow_id6; int dst_ip; int src_ip; int /*<<< orphan*/  src_ip6; int /*<<< orphan*/  dst_ip6; } ;
struct dn_flow_set {int flags_fs; int rq_size; struct dn_flow_queue** rq; int /*<<< orphan*/  rq_elements; TYPE_1__ flow_mask; } ;
struct dn_flow_queue {scalar_t__ S; scalar_t__ F; struct ip_flow_id id; struct dn_flow_queue* next; int /*<<< orphan*/ * head; } ;

/* Variables and functions */
 int /*<<< orphan*/  APPLY_MASK (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int DN_HAVE_FLOW_MASK ; 
 int /*<<< orphan*/  FREE (struct dn_flow_queue*,int /*<<< orphan*/ ) ; 
 scalar_t__ IN6_ARE_ADDR_EQUAL (TYPE_3__*,TYPE_3__*) ; 
 int IS_IP6_FLOW_ID (struct ip_flow_id*) ; 
 int /*<<< orphan*/  M_DUMMYNET ; 
 struct dn_flow_queue* create_queue (struct dn_flow_set*,int) ; 
 scalar_t__ pipe_expire ; 
 int /*<<< orphan*/  search_steps ; 
 int /*<<< orphan*/  searches ; 

__attribute__((used)) static struct dn_flow_queue *
find_queue(struct dn_flow_set *fs, struct ip_flow_id *id)
{
    int i = 0 ; /* we need i and q for new allocations */
    struct dn_flow_queue *q, *prev;
    int is_v6 = IS_IP6_FLOW_ID(id);

    if ( !(fs->flags_fs & DN_HAVE_FLOW_MASK) )
	q = fs->rq[0] ;
    else {
	/* first, do the masking, then hash */
	id->dst_port &= fs->flow_mask.dst_port ;
	id->src_port &= fs->flow_mask.src_port ;
	id->proto &= fs->flow_mask.proto ;
	id->flags = 0 ; /* we don't care about this one */
        if (is_v6) {
            APPLY_MASK(&id->dst_ip6, &fs->flow_mask.dst_ip6);
            APPLY_MASK(&id->src_ip6, &fs->flow_mask.src_ip6);
            id->flow_id6 &= fs->flow_mask.flow_id6;

            i = ((id->dst_ip6.__u6_addr.__u6_addr32[0]) & 0xffff)^
                ((id->dst_ip6.__u6_addr.__u6_addr32[1]) & 0xffff)^
                ((id->dst_ip6.__u6_addr.__u6_addr32[2]) & 0xffff)^
                ((id->dst_ip6.__u6_addr.__u6_addr32[3]) & 0xffff)^

                ((id->dst_ip6.__u6_addr.__u6_addr32[0] >> 15) & 0xffff)^
                ((id->dst_ip6.__u6_addr.__u6_addr32[1] >> 15) & 0xffff)^
                ((id->dst_ip6.__u6_addr.__u6_addr32[2] >> 15) & 0xffff)^
                ((id->dst_ip6.__u6_addr.__u6_addr32[3] >> 15) & 0xffff)^

                ((id->src_ip6.__u6_addr.__u6_addr32[0] << 1) & 0xfffff)^
                ((id->src_ip6.__u6_addr.__u6_addr32[1] << 1) & 0xfffff)^
                ((id->src_ip6.__u6_addr.__u6_addr32[2] << 1) & 0xfffff)^
                ((id->src_ip6.__u6_addr.__u6_addr32[3] << 1) & 0xfffff)^

                ((id->src_ip6.__u6_addr.__u6_addr32[0] >> 16) & 0xffff)^
                ((id->src_ip6.__u6_addr.__u6_addr32[1] >> 16) & 0xffff)^
                ((id->src_ip6.__u6_addr.__u6_addr32[2] >> 16) & 0xffff)^
                ((id->src_ip6.__u6_addr.__u6_addr32[3] >> 16) & 0xffff)^

                (id->dst_port << 1) ^ (id->src_port) ^
                (id->proto ) ^
                (id->flow_id6);
        } else {
            id->dst_ip &= fs->flow_mask.dst_ip ;
            id->src_ip &= fs->flow_mask.src_ip ;

            i = ( (id->dst_ip) & 0xffff ) ^
                ( (id->dst_ip >> 15) & 0xffff ) ^
                ( (id->src_ip << 1) & 0xffff ) ^
                ( (id->src_ip >> 16 ) & 0xffff ) ^
                (id->dst_port << 1) ^ (id->src_port) ^
                (id->proto );
        }
	i = i % fs->rq_size ;
	/* finally, scan the current list for a match */
	searches++ ;
	for (prev=NULL, q = fs->rq[i] ; q ; ) {
	    search_steps++;
            if (is_v6 &&
                    IN6_ARE_ADDR_EQUAL(&id->dst_ip6,&q->id.dst_ip6) &&
                    IN6_ARE_ADDR_EQUAL(&id->src_ip6,&q->id.src_ip6) &&
                    id->dst_port == q->id.dst_port &&
                    id->src_port == q->id.src_port &&
                    id->proto == q->id.proto &&
                    id->flags == q->id.flags &&
                    id->flow_id6 == q->id.flow_id6)
                break ; /* found */

            if (!is_v6 && id->dst_ip == q->id.dst_ip &&
                    id->src_ip == q->id.src_ip &&
                    id->dst_port == q->id.dst_port &&
                    id->src_port == q->id.src_port &&
                    id->proto == q->id.proto &&
                    id->flags == q->id.flags)
                break ; /* found */

            /* No match. Check if we can expire the entry */
	    if (pipe_expire && q->head == NULL && q->S == q->F+1 ) {
		/* entry is idle and not in any heap, expire it */
		struct dn_flow_queue *old_q = q ;

		if (prev != NULL)
		    prev->next = q = q->next ;
		else
		    fs->rq[i] = q = q->next ;
		fs->rq_elements-- ;
		FREE(old_q, M_DUMMYNET);
		continue ;
	    }
	    prev = q ;
	    q = q->next ;
	}
	if (q && prev != NULL) { /* found and not in front */
	    prev->next = q->next ;
	    q->next = fs->rq[i] ;
	    fs->rq[i] = q ;
	}
    }
    if (q == NULL) { /* no match, need to allocate a new entry */
	q = create_queue(fs, i);
	if (q != NULL)
	q->id = *id ;
    }
    return q ;
}