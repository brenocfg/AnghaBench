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
struct decode_cache {int dummy; } ;

/* Variables and functions */
 unsigned long address_mask (struct decode_cache*,unsigned long) ; 

__attribute__((used)) static inline unsigned long
register_address(struct decode_cache *c, unsigned long base, unsigned long reg)
{
	return base + address_mask(c, reg);
}