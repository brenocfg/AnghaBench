#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  __u8 ;
struct TYPE_3__ {int* c; } ;
typedef  TYPE_1__ MetricomAddress ;

/* Variables and functions */
 int /*<<< orphan*/  IS_RADIO_ADDRESS (int /*<<< orphan*/ *) ; 
 int READHEX (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int string_to_radio_address(MetricomAddress * addr, __u8 * p)
{
	if (!IS_RADIO_ADDRESS(p))
		return (1);
	addr->c[0] = 0;
	addr->c[1] = 0;
	addr->c[2] = READHEX(p[0]) << 4 | READHEX(p[1]);
	addr->c[3] = READHEX(p[2]) << 4 | READHEX(p[3]);
	addr->c[4] = READHEX(p[5]) << 4 | READHEX(p[6]);
	addr->c[5] = READHEX(p[7]) << 4 | READHEX(p[8]);
	return (0);
}