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
struct TYPE_2__ {int mode3; char reg0; int reg9; } ;

/* Variables and functions */
 TYPE_1__ d ; 
 int /*<<< orphan*/  desa_ascii (char) ; 
 int /*<<< orphan*/  desa_char (char) ; 
 int /*<<< orphan*/  desa_reg (char) ; 

__attribute__((used)) static void desa_ry_rx(int inst, int size)
{
  desa_ascii(inst);
  desa_ascii(size);
  desa_char(' ');
  if(d.mode3&1)	/* -(Ay),-(Ax) */
    {
      desa_ascii('-(A0'+d.reg0);
      desa_ascii('),-(');
      desa_ascii('A0)' + (d.reg9<<8));
    }
  else				/* Dy,Dx */
    {
      desa_reg(d.reg0);
      desa_char(',');
      desa_reg(d.reg9);
    }
}