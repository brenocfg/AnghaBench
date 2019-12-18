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
struct nouveau_i2c {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nv_mask (struct nouveau_i2c*,int,int,int) ; 

__attribute__((used)) static void
auxch_fini(struct nouveau_i2c *aux, int ch)
{
	nv_mask(aux, 0x00e4e4 + (ch * 0x50), 0x00310000, 0x00000000);
}