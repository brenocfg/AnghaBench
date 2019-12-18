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
struct nilfs_sc_info {int /*<<< orphan*/  sc_seq_request; int /*<<< orphan*/  sc_seq_done; } ;

/* Variables and functions */
 int nilfs_segctor_start_thread (struct nilfs_sc_info*) ; 

__attribute__((used)) static int nilfs_segctor_init(struct nilfs_sc_info *sci)
{
	sci->sc_seq_done = sci->sc_seq_request;

	return nilfs_segctor_start_thread(sci);
}