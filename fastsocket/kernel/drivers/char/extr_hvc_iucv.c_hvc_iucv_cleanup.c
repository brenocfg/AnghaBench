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
struct hvc_iucv_private {scalar_t__ sndbuf_len; int /*<<< orphan*/  iucv_state; int /*<<< orphan*/  tty_state; int /*<<< orphan*/  tty_inqueue; int /*<<< orphan*/  tty_outqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  IUCV_DISCONN ; 
 int /*<<< orphan*/  TTY_CLOSED ; 
 int /*<<< orphan*/  destroy_tty_buffer_list (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hvc_iucv_cleanup(struct hvc_iucv_private *priv)
{
	destroy_tty_buffer_list(&priv->tty_outqueue);
	destroy_tty_buffer_list(&priv->tty_inqueue);

	priv->tty_state = TTY_CLOSED;
	priv->iucv_state = IUCV_DISCONN;

	priv->sndbuf_len = 0;
}