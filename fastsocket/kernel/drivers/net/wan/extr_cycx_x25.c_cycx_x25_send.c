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
typedef  char u8 ;
struct cycx_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  X25_DATA_REQUEST ; 
 int x25_exec (struct cycx_device*,int /*<<< orphan*/ ,char,char**,int,void*,int) ; 

__attribute__((used)) static int cycx_x25_send(struct cycx_device *card, u8 link, u8 lcn, u8 bitm,
			 int len, void *buf)
{
	u8 d[] = "?\xFF\x10??";

	d[0] = d[3] = lcn;
	d[4] = bitm;

	return x25_exec(card, X25_DATA_REQUEST, link, &d, 5, buf, len);
}