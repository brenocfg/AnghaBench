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
struct zfcp_port {int maxframe_size; int /*<<< orphan*/  supported_classes; } ;
struct TYPE_2__ {int* common_serv_param; int* class1_serv_param; int* class2_serv_param; int* class3_serv_param; int* class4_serv_param; } ;
struct fsf_plogi {TYPE_1__ serv_param; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_COS_CLASS1 ; 
 int /*<<< orphan*/  FC_COS_CLASS2 ; 
 int /*<<< orphan*/  FC_COS_CLASS3 ; 
 int /*<<< orphan*/  FC_COS_CLASS4 ; 

void zfcp_fc_plogi_evaluate(struct zfcp_port *port, struct fsf_plogi *plogi)
{
	port->maxframe_size = plogi->serv_param.common_serv_param[7] |
		((plogi->serv_param.common_serv_param[6] & 0x0F) << 8);
	if (plogi->serv_param.class1_serv_param[0] & 0x80)
		port->supported_classes |= FC_COS_CLASS1;
	if (plogi->serv_param.class2_serv_param[0] & 0x80)
		port->supported_classes |= FC_COS_CLASS2;
	if (plogi->serv_param.class3_serv_param[0] & 0x80)
		port->supported_classes |= FC_COS_CLASS3;
	if (plogi->serv_param.class4_serv_param[0] & 0x80)
		port->supported_classes |= FC_COS_CLASS4;
}