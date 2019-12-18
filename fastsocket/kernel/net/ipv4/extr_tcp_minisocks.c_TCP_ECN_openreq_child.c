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
struct tcp_sock {int /*<<< orphan*/  ecn_flags; } ;
struct request_sock {int dummy; } ;
struct TYPE_2__ {scalar_t__ ecn_ok; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCP_ECN_OK ; 
 TYPE_1__* inet_rsk (struct request_sock*) ; 

__attribute__((used)) static inline void TCP_ECN_openreq_child(struct tcp_sock *tp,
					 struct request_sock *req)
{
	tp->ecn_flags = inet_rsk(req)->ecn_ok ? TCP_ECN_OK : 0;
}