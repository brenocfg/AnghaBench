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
struct dn_flow_set_32 {int /*<<< orphan*/  max_pkt_size; int /*<<< orphan*/  avg_pkt_size; int /*<<< orphan*/  lookup_weight; int /*<<< orphan*/  lookup_step; int /*<<< orphan*/  lookup_depth; int /*<<< orphan*/  w_q_lookup; int /*<<< orphan*/  c_4; int /*<<< orphan*/  c_3; int /*<<< orphan*/  c_2; int /*<<< orphan*/  c_1; int /*<<< orphan*/  max_p; int /*<<< orphan*/  min_th; int /*<<< orphan*/  max_th; int /*<<< orphan*/  w_q; int /*<<< orphan*/  backlogged; int /*<<< orphan*/  last_expired; int /*<<< orphan*/  rq_elements; int /*<<< orphan*/  rq_size; int /*<<< orphan*/  flow_mask; int /*<<< orphan*/  plr; int /*<<< orphan*/  qsize; int /*<<< orphan*/  weight; int /*<<< orphan*/  parent_nr; int /*<<< orphan*/  flags_fs; int /*<<< orphan*/  fs_nr; } ;
struct dn_flow_set {int /*<<< orphan*/  max_pkt_size; int /*<<< orphan*/  avg_pkt_size; int /*<<< orphan*/  lookup_weight; int /*<<< orphan*/  lookup_step; int /*<<< orphan*/  lookup_depth; int /*<<< orphan*/  w_q_lookup; int /*<<< orphan*/  c_4; int /*<<< orphan*/  c_3; int /*<<< orphan*/  c_2; int /*<<< orphan*/  c_1; int /*<<< orphan*/  max_p; int /*<<< orphan*/  min_th; int /*<<< orphan*/  max_th; int /*<<< orphan*/  w_q; int /*<<< orphan*/  backlogged; int /*<<< orphan*/  last_expired; int /*<<< orphan*/  rq_elements; int /*<<< orphan*/  rq_size; int /*<<< orphan*/  flow_mask; int /*<<< orphan*/  plr; int /*<<< orphan*/  qsize; int /*<<< orphan*/  weight; int /*<<< orphan*/  parent_nr; int /*<<< orphan*/  flags_fs; int /*<<< orphan*/  fs_nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAST_DOWN_EXPLICIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  user32_addr_t ; 

__attribute__((used)) static void
cp_flow_set_to_32_user(struct dn_flow_set *set, struct dn_flow_set_32 *fs_bp)
{
	fs_bp->fs_nr = set->fs_nr;
	fs_bp->flags_fs = set->flags_fs ;
	fs_bp->parent_nr = set->parent_nr ;
	fs_bp->weight = set->weight ;
	fs_bp->qsize = set->qsize ;
	fs_bp->plr = set->plr ;
	fs_bp->flow_mask = set->flow_mask ;
	fs_bp->rq_size = set->rq_size ;
	fs_bp->rq_elements = set->rq_elements ;
	fs_bp->last_expired = set->last_expired ;
	fs_bp->backlogged = set->backlogged ;
	fs_bp->w_q = set->w_q ;
	fs_bp->max_th = set->max_th ;
	fs_bp->min_th = set->min_th ;
	fs_bp->max_p = set->max_p ;
	fs_bp->c_1 = set->c_1 ;
	fs_bp->c_2 = set->c_2 ;
	fs_bp->c_3 = set->c_3 ;
	fs_bp->c_4 = set->c_4 ;
	fs_bp->w_q_lookup = CAST_DOWN_EXPLICIT(user32_addr_t, set->w_q_lookup) ;
	fs_bp->lookup_depth = set->lookup_depth ;
	fs_bp->lookup_step = set->lookup_step ;
	fs_bp->lookup_weight = set->lookup_weight ;
	fs_bp->avg_pkt_size = set->avg_pkt_size ;
	fs_bp->max_pkt_size = set->max_pkt_size ;
}