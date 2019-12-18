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
typedef  int /*<<< orphan*/  u_int32_t ;
struct TYPE_2__ {int sb_flags; } ;
struct socket {TYPE_1__ so_snd; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int SB_SNDBYTE_CNT ; 
 int /*<<< orphan*/  inp_decr_sndbytes_unsent (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inp_get_sndbytes_allunsent (struct socket*,int /*<<< orphan*/ ) ; 

inline void
inp_decr_sndbytes_allunsent(struct socket *so, u_int32_t th_ack)
{
	int32_t len;

	if (so == NULL || !(so->so_snd.sb_flags & SB_SNDBYTE_CNT))
		return;

	len = inp_get_sndbytes_allunsent(so, th_ack);
	inp_decr_sndbytes_unsent(so, len);
}