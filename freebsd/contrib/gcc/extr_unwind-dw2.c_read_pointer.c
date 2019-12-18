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
union unaligned {void* p; } ;

/* Variables and functions */

__attribute__((used)) static inline void *
read_pointer (const void *p) { const union unaligned *up = p; return up->p; }