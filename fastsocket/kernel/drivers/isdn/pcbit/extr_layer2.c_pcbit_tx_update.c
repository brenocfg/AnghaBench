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
typedef  int /*<<< orphan*/  ushort ;
typedef  int u_char ;
struct pcbit_dev {int send_seq; int rcv_seq; scalar_t__ sh_mem; int /*<<< orphan*/ * fsize; } ;

/* Variables and functions */
 scalar_t__ BANK4 ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static __inline__ void
pcbit_tx_update(struct pcbit_dev *dev, ushort len)
{
	u_char info;

	dev->send_seq = (dev->send_seq + 1) % 8;

	dev->fsize[dev->send_seq] = len;
	info = 0;
	info |= dev->rcv_seq << 3;
	info |= dev->send_seq;

	writeb(info, dev->sh_mem + BANK4);

}