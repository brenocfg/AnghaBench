#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned char* zram; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_IO ; 
 TYPE_1__ Pico ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,unsigned int,unsigned char) ; 
 int /*<<< orphan*/  write_bank (unsigned int,unsigned char) ; 

__attribute__((used)) static void xwrite(unsigned int a, unsigned char d)
{
  elprintf(EL_IO, "z80 write [%04x] %02x", a, d);
  if (a >= 0xc000)
    Pico.zram[a & 0x1fff] = d;
  if (a >= 0xfff8)
    write_bank(a, d);
}