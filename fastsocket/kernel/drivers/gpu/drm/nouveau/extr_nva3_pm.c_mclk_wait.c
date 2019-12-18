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
typedef  int u32 ;
struct nouveau_mem_exec_func {int /*<<< orphan*/  dev; } ;
struct nouveau_device {int dummy; } ;

/* Variables and functions */
 struct nouveau_device* nouveau_dev (int /*<<< orphan*/ ) ; 
 int nv_rd32 (struct nouveau_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void
mclk_wait(struct nouveau_mem_exec_func *exec, u32 nsec)
{
	struct nouveau_device *device = nouveau_dev(exec->dev);
	volatile u32 post = nv_rd32(device, 0); (void)post;
	udelay((nsec + 500) / 1000);
}