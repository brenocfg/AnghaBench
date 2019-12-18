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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ _iobase ; 
 scalar_t__ ioread32 (scalar_t__) ; 

__attribute__((used)) static inline void
_readfield(u32 offset, void *value)
{
	int i;
	for(i = 0; i < 4; i++)
		((u32 *) value)[i] = ioread32(_iobase + offset + (i * 4));
}