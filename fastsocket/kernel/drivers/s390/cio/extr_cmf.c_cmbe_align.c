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
struct cmbe {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct cmbe *cmbe_align(struct cmbe *c)
{
	unsigned long addr;
	addr = ((unsigned long)c + sizeof (struct cmbe) - sizeof(long)) &
				 ~(sizeof (struct cmbe) - sizeof(long));
	return (struct cmbe*)addr;
}