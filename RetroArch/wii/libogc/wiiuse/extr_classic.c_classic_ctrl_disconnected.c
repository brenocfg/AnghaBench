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
struct classic_ctrl_t {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct classic_ctrl_t*,int /*<<< orphan*/ ,int) ; 

void classic_ctrl_disconnected(struct classic_ctrl_t* cc)
{
	memset(cc, 0, sizeof(struct classic_ctrl_t));
}