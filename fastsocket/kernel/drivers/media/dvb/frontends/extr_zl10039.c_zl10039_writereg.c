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
typedef  int /*<<< orphan*/  u8 ;
struct zl10039_state {int dummy; } ;
typedef  enum zl10039_reg_addr { ____Placeholder_zl10039_reg_addr } zl10039_reg_addr ;

/* Variables and functions */
 int zl10039_write (struct zl10039_state*,int const,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static inline int zl10039_writereg(struct zl10039_state *state,
				const enum zl10039_reg_addr reg,
				const u8 val)
{
	return zl10039_write(state, reg, &val, 1);
}