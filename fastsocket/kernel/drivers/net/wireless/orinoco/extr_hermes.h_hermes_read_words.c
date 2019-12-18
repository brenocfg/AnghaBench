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
struct hermes {int reg_spacing; scalar_t__ iobase; } ;

/* Variables and functions */
 int /*<<< orphan*/  ioread16_rep (scalar_t__,void*,unsigned int) ; 

__attribute__((used)) static inline void hermes_read_words(struct hermes *hw, int off,
				     void *buf, unsigned count)
{
	off = off << hw->reg_spacing;
	ioread16_rep(hw->iobase + off, buf, count);
}