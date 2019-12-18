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

/* Variables and functions */
 scalar_t__ ANSLCD_DATA_IX ; 
 scalar_t__ anslcd_ptr ; 
 int /*<<< orphan*/  anslcd_short_delay ; 
 int /*<<< orphan*/  out_8 (scalar_t__,unsigned char) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
anslcd_write_byte_data ( unsigned char c )
{
	out_8(anslcd_ptr + ANSLCD_DATA_IX, c);
	udelay(anslcd_short_delay);
}