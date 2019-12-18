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
struct nv84_fifo_priv {int dummy; } ;
struct nouveau_event {struct nv84_fifo_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  nv_mask (struct nv84_fifo_priv*,int,int,int) ; 

__attribute__((used)) static void
nv84_fifo_uevent_enable(struct nouveau_event *event, int index)
{
	struct nv84_fifo_priv *priv = event->priv;
	nv_mask(priv, 0x002140, 0x40000000, 0x40000000);
}