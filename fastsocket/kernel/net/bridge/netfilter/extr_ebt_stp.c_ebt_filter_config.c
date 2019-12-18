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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct stp_config_pdu {scalar_t__ flags; int* root; int* sender; int* port; int* msg_age; int* max_age; int* hello_time; int* forward_delay; int /*<<< orphan*/  root_cost; } ;
struct ebt_stp_config_info {scalar_t__ flags; scalar_t__ root_priol; scalar_t__ root_priou; int* root_addr; int* root_addrmsk; scalar_t__ root_costl; scalar_t__ root_costu; scalar_t__ sender_priol; scalar_t__ sender_priou; int* sender_addr; int* sender_addrmsk; scalar_t__ portl; scalar_t__ portu; scalar_t__ msg_agel; scalar_t__ msg_ageu; scalar_t__ max_agel; scalar_t__ max_ageu; scalar_t__ hello_timel; scalar_t__ hello_timeu; scalar_t__ forward_delayl; scalar_t__ forward_delayu; } ;
struct ebt_stp_info {int bitmask; struct ebt_stp_config_info config; } ;

/* Variables and functions */
 int EBT_STP_FLAGS ; 
 int EBT_STP_FWDD ; 
 int EBT_STP_HELLOTIME ; 
 int EBT_STP_MAXAGE ; 
 int EBT_STP_MSGAGE ; 
 int EBT_STP_PORT ; 
 int EBT_STP_ROOTADDR ; 
 int EBT_STP_ROOTCOST ; 
 int EBT_STP_ROOTPRIO ; 
 int EBT_STP_SENDERADDR ; 
 int EBT_STP_SENDERPRIO ; 
 scalar_t__ FWINV (int,int) ; 
 scalar_t__ NR16 (int*) ; 
 scalar_t__ NR32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ebt_filter_config(const struct ebt_stp_info *info,
   const struct stp_config_pdu *stpc)
{
	const struct ebt_stp_config_info *c;
	uint16_t v16;
	uint32_t v32;
	int verdict, i;

	c = &info->config;
	if ((info->bitmask & EBT_STP_FLAGS) &&
	    FWINV(c->flags != stpc->flags, EBT_STP_FLAGS))
		return false;
	if (info->bitmask & EBT_STP_ROOTPRIO) {
		v16 = NR16(stpc->root);
		if (FWINV(v16 < c->root_priol ||
		    v16 > c->root_priou, EBT_STP_ROOTPRIO))
			return false;
	}
	if (info->bitmask & EBT_STP_ROOTADDR) {
		verdict = 0;
		for (i = 0; i < 6; i++)
			verdict |= (stpc->root[2+i] ^ c->root_addr[i]) &
				   c->root_addrmsk[i];
		if (FWINV(verdict != 0, EBT_STP_ROOTADDR))
			return false;
	}
	if (info->bitmask & EBT_STP_ROOTCOST) {
		v32 = NR32(stpc->root_cost);
		if (FWINV(v32 < c->root_costl ||
		    v32 > c->root_costu, EBT_STP_ROOTCOST))
			return false;
	}
	if (info->bitmask & EBT_STP_SENDERPRIO) {
		v16 = NR16(stpc->sender);
		if (FWINV(v16 < c->sender_priol ||
		    v16 > c->sender_priou, EBT_STP_SENDERPRIO))
			return false;
	}
	if (info->bitmask & EBT_STP_SENDERADDR) {
		verdict = 0;
		for (i = 0; i < 6; i++)
			verdict |= (stpc->sender[2+i] ^ c->sender_addr[i]) &
				   c->sender_addrmsk[i];
		if (FWINV(verdict != 0, EBT_STP_SENDERADDR))
			return false;
	}
	if (info->bitmask & EBT_STP_PORT) {
		v16 = NR16(stpc->port);
		if (FWINV(v16 < c->portl ||
		    v16 > c->portu, EBT_STP_PORT))
			return false;
	}
	if (info->bitmask & EBT_STP_MSGAGE) {
		v16 = NR16(stpc->msg_age);
		if (FWINV(v16 < c->msg_agel ||
		    v16 > c->msg_ageu, EBT_STP_MSGAGE))
			return false;
	}
	if (info->bitmask & EBT_STP_MAXAGE) {
		v16 = NR16(stpc->max_age);
		if (FWINV(v16 < c->max_agel ||
		    v16 > c->max_ageu, EBT_STP_MAXAGE))
			return false;
	}
	if (info->bitmask & EBT_STP_HELLOTIME) {
		v16 = NR16(stpc->hello_time);
		if (FWINV(v16 < c->hello_timel ||
		    v16 > c->hello_timeu, EBT_STP_HELLOTIME))
			return false;
	}
	if (info->bitmask & EBT_STP_FWDD) {
		v16 = NR16(stpc->forward_delay);
		if (FWINV(v16 < c->forward_delayl ||
		    v16 > c->forward_delayu, EBT_STP_FWDD))
			return false;
	}
	return true;
}