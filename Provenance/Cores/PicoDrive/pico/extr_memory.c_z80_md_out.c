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
 int /*<<< orphan*/  EL_ANOMALY ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,unsigned short,unsigned char) ; 

__attribute__((used)) static void z80_md_out(unsigned short p, unsigned char d)
{
  elprintf(EL_ANOMALY, "Z80 port %04x write %02x", p, d);
}