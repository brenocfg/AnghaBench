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
typedef  int /*<<< orphan*/  d ;

/* Variables and functions */
 int /*<<< orphan*/  X25_DISCONNECT_RESPONSE ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int x25_exec (struct cycx_device*,int /*<<< orphan*/ ,char,char**,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cycx_x25_disconnect_response(struct cycx_device *card, u8 link,
					u8 lcn)
{
	char d[5];

	memset(d, 0, sizeof(d));
	d[0] = d[3] = lcn;
	d[2] = 0x10;
	d[4] = 0x17;

	return x25_exec(card, X25_DISCONNECT_RESPONSE, link, &d, 5, NULL, 0);
}