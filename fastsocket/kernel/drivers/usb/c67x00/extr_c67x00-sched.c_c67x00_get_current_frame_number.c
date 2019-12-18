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
typedef  int u16 ;
struct c67x00_hcd {int /*<<< orphan*/  sie; } ;

/* Variables and functions */
 int HOST_FRAME_MASK ; 
 int c67x00_ll_husb_get_frame (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u16 c67x00_get_current_frame_number(struct c67x00_hcd *c67x00)
{
	return c67x00_ll_husb_get_frame(c67x00->sie) & HOST_FRAME_MASK;
}