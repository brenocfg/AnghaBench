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

/* Variables and functions */
 scalar_t__ atomic_load (int /*<<< orphan*/ *) ; 
 scalar_t__ received_nb_signals ; 
 int /*<<< orphan*/  transcode_init_done ; 

__attribute__((used)) static int decode_interrupt_cb(void *ctx)
{
    return received_nb_signals > atomic_load(&transcode_init_done);
}