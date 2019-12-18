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
struct TYPE_2__ {int w; scalar_t__ reg0; scalar_t__ reg9; } ;

/* Variables and functions */
 TYPE_1__ d ; 
 int /*<<< orphan*/  desa_ascii (char) ; 
 int /*<<< orphan*/  desa_char (char) ; 
 int /*<<< orphan*/  desa_reg (scalar_t__) ; 

__attribute__((used)) static int check_desa_exg()
{
  unsigned int reg;
  switch(d.w&0770)
    {
    case 0500:
      reg = 0x0000;
      break;
    case 0510:
      reg = 0x0808;
      break;
    case 0610:
      reg = 0x0008;
      break;
    default:
      return 0;
    }
  desa_ascii('EXG ');
  desa_reg(d.reg9 + (reg>>8));
  desa_char (',');
  desa_reg(d.reg0 + (reg&8));
  return 1;
}