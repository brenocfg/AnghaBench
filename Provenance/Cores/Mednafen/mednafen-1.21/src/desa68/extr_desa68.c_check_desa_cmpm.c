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
struct TYPE_2__ {int w; char reg0; int reg9; } ;

/* Variables and functions */
 TYPE_1__ d ; 
 int /*<<< orphan*/  desa_ascii (char) ; 

__attribute__((used)) static int check_desa_cmpm()
{
  if((d.w&0470)!=0410/* || (d.w&0300)==0300 */)
    return 0;
  desa_ascii('CMPM');
  desa_ascii(' (A0' + d.reg0);
  desa_ascii(')+,(');
  desa_ascii('A0)+' + (d.reg9<<16));
  return 1;
}