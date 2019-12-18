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
struct inet_diag_hostcond {int port; int /*<<< orphan*/  prefix_len; int /*<<< orphan*/  addr; int /*<<< orphan*/  family; } ;
struct inet_diag_entry {int sport; int dport; int userlocks; int /*<<< orphan*/  family; int /*<<< orphan*/ * daddr; int /*<<< orphan*/ * saddr; } ;
struct inet_diag_bc_op {int code; int no; scalar_t__ yes; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
#define  INET_DIAG_BC_AUTO 136 
#define  INET_DIAG_BC_D_COND 135 
#define  INET_DIAG_BC_D_GE 134 
#define  INET_DIAG_BC_D_LE 133 
#define  INET_DIAG_BC_JMP 132 
#define  INET_DIAG_BC_NOP 131 
#define  INET_DIAG_BC_S_COND 130 
#define  INET_DIAG_BC_S_GE 129 
#define  INET_DIAG_BC_S_LE 128 
 int SOCK_BINDPORT_LOCK ; 
 int /*<<< orphan*/  bitstring_match (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int) ; 

__attribute__((used)) static int inet_diag_bc_run(const void *bc, int len,
			    const struct inet_diag_entry *entry)
{
	while (len > 0) {
		int yes = 1;
		const struct inet_diag_bc_op *op = bc;

		switch (op->code) {
		case INET_DIAG_BC_NOP:
			break;
		case INET_DIAG_BC_JMP:
			yes = 0;
			break;
		case INET_DIAG_BC_S_GE:
			yes = entry->sport >= op[1].no;
			break;
		case INET_DIAG_BC_S_LE:
			yes = entry->dport <= op[1].no;
			break;
		case INET_DIAG_BC_D_GE:
			yes = entry->dport >= op[1].no;
			break;
		case INET_DIAG_BC_D_LE:
			yes = entry->dport <= op[1].no;
			break;
		case INET_DIAG_BC_AUTO:
			yes = !(entry->userlocks & SOCK_BINDPORT_LOCK);
			break;
		case INET_DIAG_BC_S_COND:
		case INET_DIAG_BC_D_COND: {
			struct inet_diag_hostcond *cond;
			__be32 *addr;

			cond = (struct inet_diag_hostcond *)(op + 1);
			if (cond->port != -1 &&
			    cond->port != (op->code == INET_DIAG_BC_S_COND ?
					     entry->sport : entry->dport)) {
				yes = 0;
				break;
			}

			if (cond->prefix_len == 0)
				break;

			if (op->code == INET_DIAG_BC_S_COND)
				addr = entry->saddr;
			else
				addr = entry->daddr;

			if (bitstring_match(addr, cond->addr,
					    cond->prefix_len))
				break;
			if (entry->family == AF_INET6 &&
			    cond->family == AF_INET) {
				if (addr[0] == 0 && addr[1] == 0 &&
				    addr[2] == htonl(0xffff) &&
				    bitstring_match(addr + 3, cond->addr,
						    cond->prefix_len))
					break;
			}
			yes = 0;
			break;
		}
		}

		if (yes) {
			len -= op->yes;
			bc += op->yes;
		} else {
			len -= op->no;
			bc += op->no;
		}
	}
	return (len == 0);
}