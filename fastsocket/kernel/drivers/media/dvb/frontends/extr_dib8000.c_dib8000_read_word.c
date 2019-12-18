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
struct dib8000_state {int /*<<< orphan*/  i2c; } ;

/* Variables and functions */
 int /*<<< orphan*/  dib8000_i2c_read16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 dib8000_read_word(struct dib8000_state *state, u16 reg)
{
	return dib8000_i2c_read16(&state->i2c, reg);
}