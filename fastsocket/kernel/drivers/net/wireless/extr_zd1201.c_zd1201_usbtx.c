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
struct zd1201 {int /*<<< orphan*/  dev; } ;
struct urb {struct zd1201* context; } ;

/* Variables and functions */
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zd1201_usbtx(struct urb *urb)
{
	struct zd1201 *zd = urb->context;
	netif_wake_queue(zd->dev);
	return;
}