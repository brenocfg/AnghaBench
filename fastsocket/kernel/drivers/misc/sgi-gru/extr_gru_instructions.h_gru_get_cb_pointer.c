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
 int GRU_CB_BASE ; 
 int GRU_HANDLE_STRIDE ; 

__attribute__((used)) static inline void *gru_get_cb_pointer(void *gseg,
						      int index)
{
	return gseg + GRU_CB_BASE + index * GRU_HANDLE_STRIDE;
}