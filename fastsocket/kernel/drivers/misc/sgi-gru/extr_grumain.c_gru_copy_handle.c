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
 long GRU_HANDLE_BYTES ; 
 int /*<<< orphan*/  memcpy (void*,void*,long) ; 

__attribute__((used)) static inline long gru_copy_handle(void *d, void *s)
{
	memcpy(d, s, GRU_HANDLE_BYTES);
	return GRU_HANDLE_BYTES;
}