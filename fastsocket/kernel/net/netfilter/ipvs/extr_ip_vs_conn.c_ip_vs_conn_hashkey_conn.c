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
struct ip_vs_conn_param {int /*<<< orphan*/  pe_data_len; int /*<<< orphan*/  pe_data; scalar_t__ pe; } ;
struct ip_vs_conn {int /*<<< orphan*/  pe_data_len; int /*<<< orphan*/  pe_data; scalar_t__ pe; int /*<<< orphan*/  cport; int /*<<< orphan*/  caddr; int /*<<< orphan*/  protocol; int /*<<< orphan*/  af; } ;

/* Variables and functions */
 int /*<<< orphan*/  ip_vs_conn_fill_param (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ip_vs_conn_param*) ; 
 unsigned int ip_vs_conn_hashkey_param (struct ip_vs_conn_param*,int) ; 

__attribute__((used)) static unsigned int ip_vs_conn_hashkey_conn(const struct ip_vs_conn *cp)
{
	struct ip_vs_conn_param p;

	ip_vs_conn_fill_param(cp->af, cp->protocol, &cp->caddr, cp->cport,
			      NULL, 0, &p);

	if (cp->pe) {
		p.pe = cp->pe;
		p.pe_data = cp->pe_data;
		p.pe_data_len = cp->pe_data_len;
	}

	return ip_vs_conn_hashkey_param(&p, false);
}