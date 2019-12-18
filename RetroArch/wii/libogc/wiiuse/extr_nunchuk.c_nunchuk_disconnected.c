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
struct nunchuk_t {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct nunchuk_t*,int /*<<< orphan*/ ,int) ; 

void nunchuk_disconnected(struct nunchuk_t* nc)
{
	//printf("nunchuk_disconnected()\n");
	memset(nc, 0, sizeof(struct nunchuk_t));
}