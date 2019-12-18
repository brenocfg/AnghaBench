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
struct riscom_board {scalar_t__ base; } ;

/* Variables and functions */
 int RC_NIOPORT ; 
 scalar_t__ RC_TO_ISA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rc_ioport ; 
 int /*<<< orphan*/  release_region (scalar_t__,int) ; 

__attribute__((used)) static void rc_release_io_range(struct riscom_board * const bp)
{
	int i;

	for (i = 0; i < RC_NIOPORT; i++)
		release_region(RC_TO_ISA(rc_ioport[i]) + bp->base, 1);
}