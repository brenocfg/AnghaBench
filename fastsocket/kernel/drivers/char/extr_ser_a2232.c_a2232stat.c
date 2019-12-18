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
struct a2232status {int dummy; } ;
struct a2232memory {struct a2232status volatile* Status; } ;

/* Variables and functions */
 struct a2232memory* a2232mem (unsigned int) ; 

__attribute__((used)) static inline volatile struct a2232status *a2232stat(unsigned int board,
						     unsigned int portonboard)
{
	volatile struct a2232memory *mem = a2232mem(board);
	return &(mem->Status[portonboard]);
}