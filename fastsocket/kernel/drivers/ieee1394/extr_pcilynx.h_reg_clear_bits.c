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
typedef  int u32 ;
struct ti_lynx {int dummy; } ;

/* Variables and functions */
 int reg_read (struct ti_lynx const*,int) ; 
 int /*<<< orphan*/  reg_write (struct ti_lynx const*,int,int) ; 

__attribute__((used)) static inline void reg_clear_bits(const struct ti_lynx *lynx, int offset,
                                  u32 mask)
{
        reg_write(lynx, offset, (reg_read(lynx, offset) & ~mask));
}