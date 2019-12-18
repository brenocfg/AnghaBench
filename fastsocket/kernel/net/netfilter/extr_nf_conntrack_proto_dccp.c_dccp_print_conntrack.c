#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int dummy; } ;
struct TYPE_3__ {size_t state; } ;
struct TYPE_4__ {TYPE_1__ dccp; } ;
struct nf_conn {TYPE_2__ proto; } ;

/* Variables and functions */
 int /*<<< orphan*/ * dccp_state_names ; 
 int seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dccp_print_conntrack(struct seq_file *s, struct nf_conn *ct)
{
	return seq_printf(s, "%s ", dccp_state_names[ct->proto.dccp.state]);
}