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
typedef  int u8 ;
struct sock {int dummy; } ;
struct htcp {int /*<<< orphan*/  undo_last_cong; int /*<<< orphan*/  last_cong; } ;

/* Variables and functions */
#define  TCP_CA_CWR 131 
#define  TCP_CA_Loss 130 
#define  TCP_CA_Open 129 
#define  TCP_CA_Recovery 128 
 int /*<<< orphan*/  htcp_reset (struct htcp*) ; 
 struct htcp* inet_csk_ca (struct sock*) ; 
 int /*<<< orphan*/  jiffies ; 

__attribute__((used)) static void htcp_state(struct sock *sk, u8 new_state)
{
	switch (new_state) {
	case TCP_CA_Open:
		{
			struct htcp *ca = inet_csk_ca(sk);
			if (ca->undo_last_cong) {
				ca->last_cong = jiffies;
				ca->undo_last_cong = 0;
			}
		}
		break;
	case TCP_CA_CWR:
	case TCP_CA_Recovery:
	case TCP_CA_Loss:
		htcp_reset(inet_csk_ca(sk));
		break;
	}
}