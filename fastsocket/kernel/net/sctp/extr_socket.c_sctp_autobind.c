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
typedef  union sctp_addr {int dummy; } sctp_addr ;
struct sock {int dummy; } ;
struct sctp_af {int /*<<< orphan*/  sockaddr_len; int /*<<< orphan*/  (* inaddr_any ) (union sctp_addr*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_6__ {int /*<<< orphan*/  num; } ;
struct TYPE_5__ {TYPE_1__* pf; } ;
struct TYPE_4__ {struct sctp_af* af; } ;

/* Variables and functions */
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 TYPE_3__* inet_sk (struct sock*) ; 
 int sctp_do_bind (struct sock*,union sctp_addr*,int /*<<< orphan*/ ) ; 
 TYPE_2__* sctp_sk (struct sock*) ; 
 int /*<<< orphan*/  stub1 (union sctp_addr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sctp_autobind(struct sock *sk)
{
	union sctp_addr autoaddr;
	struct sctp_af *af;
	__be16 port;

	/* Initialize a local sockaddr structure to INADDR_ANY. */
	af = sctp_sk(sk)->pf->af;

	port = htons(inet_sk(sk)->num);
	af->inaddr_any(&autoaddr, port);

	return sctp_do_bind(sk, &autoaddr, af->sockaddr_len);
}