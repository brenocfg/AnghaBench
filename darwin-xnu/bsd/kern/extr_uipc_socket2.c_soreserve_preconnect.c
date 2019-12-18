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
struct TYPE_4__ {unsigned int sb_preconn_hiwat; } ;
struct TYPE_3__ {unsigned int sb_preconn_hiwat; } ;
struct socket {TYPE_2__ so_rcv; TYPE_1__ so_snd; } ;

/* Variables and functions */

void
soreserve_preconnect(struct socket *so, unsigned int pre_cc)
{
	/* As of now, same bytes for both preconnect read and write */
	so->so_snd.sb_preconn_hiwat = pre_cc;
	so->so_rcv.sb_preconn_hiwat = pre_cc;
}