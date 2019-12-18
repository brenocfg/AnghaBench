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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int u_char ;

/* Variables and functions */
 int /*<<< orphan*/  VCC_0V ; 
 int /*<<< orphan*/  VCC_3V ; 
 int /*<<< orphan*/  VCC_5V ; 

__attribute__((used)) static inline uint8_t set_Vcc_value(u_char Vcc)
{
	switch (Vcc) {
	case 33:
		return VCC_3V;
	case 50:
		return VCC_5V;
	}

	return VCC_0V;
}