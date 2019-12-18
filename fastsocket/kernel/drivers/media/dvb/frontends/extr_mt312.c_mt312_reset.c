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
typedef  scalar_t__ u8 ;
struct mt312_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RESET ; 
 int mt312_writereg (struct mt312_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mt312_reset(struct mt312_state *state, const u8 full)
{
	return mt312_writereg(state, RESET, full ? 0x80 : 0x40);
}