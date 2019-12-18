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
typedef  int /*<<< orphan*/  u_int ;
struct scb {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline
void ahc_set_transaction_tag(struct scb *scb, int enabled, u_int type)
{
	/*
	 * Nothing to do for linux as the incoming transaction
	 * has no concept of tag/non tagged, etc.
	 */
}