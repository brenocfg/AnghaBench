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
struct ip_vs_seq {int /*<<< orphan*/  previous_delta; int /*<<< orphan*/  delta; int /*<<< orphan*/  init_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_unaligned_be32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hton_seq(struct ip_vs_seq *ho, struct ip_vs_seq *no)
{
	put_unaligned_be32(ho->init_seq, &no->init_seq);
	put_unaligned_be32(ho->delta, &no->delta);
	put_unaligned_be32(ho->previous_delta, &no->previous_delta);
}