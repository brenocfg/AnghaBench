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
struct TYPE_2__ {int w; int adrmode0; int line; } ;

/* Variables and functions */
 TYPE_1__ d ; 
 int /*<<< orphan*/  desa_dn_ae (char) ; 

__attribute__((used)) static int check_desa_and_or(void)
{
  int modemsk = !(d.w&0400)? 0xFFD : 0x1FC;
  if(!(modemsk&(1<<d.adrmode0)))
    return 0;
  desa_dn_ae((d.line==0xC)? 'AND' : 'OR');
  return 1;
}