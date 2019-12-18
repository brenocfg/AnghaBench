#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  port; } ;
struct TYPE_11__ {TYPE_4__ tcp; } ;
struct TYPE_12__ {TYPE_5__ u; } ;
struct TYPE_7__ {int /*<<< orphan*/  port; } ;
struct TYPE_8__ {TYPE_1__ tcp; } ;
struct TYPE_9__ {TYPE_2__ u; } ;
struct nf_conntrack_tuple {TYPE_6__ dst; TYPE_3__ src; } ;

/* Variables and functions */
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tcp_print_tuple(struct seq_file *s,
			   const struct nf_conntrack_tuple *tuple)
{
	return seq_printf(s, "sport=%hu dport=%hu ",
			  ntohs(tuple->src.u.tcp.port),
			  ntohs(tuple->dst.u.tcp.port));
}