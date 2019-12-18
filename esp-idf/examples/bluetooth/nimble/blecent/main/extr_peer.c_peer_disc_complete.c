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
struct peer {int /*<<< orphan*/  disc_cb_arg; int /*<<< orphan*/  (* disc_cb ) (struct peer*,int,int /*<<< orphan*/ ) ;scalar_t__ disc_prev_chr_val; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct peer*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
peer_disc_complete(struct peer *peer, int rc)
{
    peer->disc_prev_chr_val = 0;

    /* Notify caller that discovery has completed. */
    if (peer->disc_cb != NULL) {
        peer->disc_cb(peer, rc, peer->disc_cb_arg);
    }
}