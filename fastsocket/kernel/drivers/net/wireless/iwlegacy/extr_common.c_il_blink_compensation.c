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
typedef  int u8 ;
typedef  int u16 ;
struct il_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IL_ERR (char*) ; 

__attribute__((used)) static inline u8
il_blink_compensation(struct il_priv *il, u8 time, u16 compensation)
{
	if (!compensation) {
		IL_ERR("undefined blink compensation: "
		       "use pre-defined blinking time\n");
		return time;
	}

	return (u8) ((time * compensation) >> 6);
}