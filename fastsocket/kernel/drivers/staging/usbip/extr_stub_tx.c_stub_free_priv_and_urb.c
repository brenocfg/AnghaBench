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
struct urb {int /*<<< orphan*/  transfer_buffer; int /*<<< orphan*/  setup_packet; } ;
struct stub_priv {int /*<<< orphan*/  list; struct urb* urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct stub_priv*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub_priv_cache ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 

__attribute__((used)) static void stub_free_priv_and_urb(struct stub_priv *priv)
{
	struct urb *urb = priv->urb;

	kfree(urb->setup_packet);
	kfree(urb->transfer_buffer);
	list_del(&priv->list);
	kmem_cache_free(stub_priv_cache, priv);
	usb_free_urb(urb);
}