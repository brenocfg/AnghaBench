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
struct cycx_x25_channel {int lcn; int /*<<< orphan*/  link; } ;
struct cycx_device {int dummy; } ;
typedef  int /*<<< orphan*/  d ;

/* Variables and functions */
 int /*<<< orphan*/  X25_CONNECT_RESPONSE ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int x25_exec (struct cycx_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int**,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cycx_x25_connect_response(struct cycx_device *card,
				     struct cycx_x25_channel *chan)
{
	u8 d[8];

	memset(d, 0, sizeof(d));
	d[0] = d[3] = chan->lcn;
	d[2] = 0x10;
	d[4] = 0x0F;
	d[7] = 0xCC; /* TCP/IP over X.25, thanks Daniela */

	return x25_exec(card, X25_CONNECT_RESPONSE, chan->link, &d, 8, NULL, 0);
}