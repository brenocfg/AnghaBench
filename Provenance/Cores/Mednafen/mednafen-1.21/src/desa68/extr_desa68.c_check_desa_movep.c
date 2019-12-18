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
struct TYPE_2__ {int w; int opsz; char reg9; int /*<<< orphan*/  reg0; } ;

/* Variables and functions */
 int /*<<< orphan*/  MODE_dAN ; 
 TYPE_1__ d ; 
 int /*<<< orphan*/  desa_ascii (char) ; 
 int /*<<< orphan*/  desa_str (char*) ; 
 int /*<<< orphan*/  get_ea_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_desa_movep(void)
{
  if((d.w & 0470) != 0410 )
    return 0;

  desa_str("MOVEP.");
  desa_ascii((d.opsz&1)?'L ' : 'W ');

  /* MOVEP.? d(Ax),Dy */
  if(!(d.w&(1<<7)))
    {
      get_ea_2(MODE_dAN, d.reg0, 0 );
      desa_ascii(',D0' + d.reg9 );
    }
  /* MOVEP.? Dx,d(Ay) */
  else
    {
      desa_ascii('D0,' + (d.reg9<<8) );
      get_ea_2(MODE_dAN, d.reg0, 0 );
    }
  return 1;
}