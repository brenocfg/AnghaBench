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
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  hfa384x_t ;

/* Variables and functions */
 int /*<<< orphan*/  DOWAIT ; 
 int hfa384x_dormem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int
hfa384x_dormem_wait(hfa384x_t *hw,
		    u16 page, u16 offset, void *data, unsigned int len)
{
	return hfa384x_dormem(hw, DOWAIT,
			      page, offset, data, len, NULL, NULL, NULL);
}