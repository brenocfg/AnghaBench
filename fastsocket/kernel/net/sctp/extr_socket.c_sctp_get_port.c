#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  sin_port; } ;
union sctp_addr {TYPE_2__ v4; } ;
struct sock {int dummy; } ;
struct sctp_af {int /*<<< orphan*/  (* from_sk ) (union sctp_addr*,struct sock*) ;} ;
struct TYPE_6__ {TYPE_1__* pf; } ;
struct TYPE_4__ {struct sctp_af* af; } ;

/* Variables and functions */
 int /*<<< orphan*/  htons (unsigned short) ; 
 long sctp_get_port_local (struct sock*,union sctp_addr*) ; 
 TYPE_3__* sctp_sk (struct sock*) ; 
 int /*<<< orphan*/  stub1 (union sctp_addr*,struct sock*) ; 

__attribute__((used)) static int sctp_get_port(struct sock *sk, unsigned short snum)
{
	long ret;
	union sctp_addr addr;
	struct sctp_af *af = sctp_sk(sk)->pf->af;

	/* Set up a dummy address struct from the sk. */
	af->from_sk(&addr, sk);
	addr.v4.sin_port = htons(snum);

	/* Note: sk->sk_num gets filled in if ephemeral port request. */
	ret = sctp_get_port_local(sk, &addr);

	return (ret ? 1 : 0);
}