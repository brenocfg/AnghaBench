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
struct board_info {scalar_t__ port; } ;

/* Variables and functions */
 unsigned int FEPWIN ; 
 int /*<<< orphan*/  outb_p (unsigned int,scalar_t__) ; 

__attribute__((used)) static void pcxem_memwinon(struct board_info *b, unsigned int win)
{
	outb_p(FEPWIN | win, b->port + 1);
}