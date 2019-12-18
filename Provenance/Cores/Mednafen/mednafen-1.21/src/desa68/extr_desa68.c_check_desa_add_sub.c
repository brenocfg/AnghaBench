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
struct TYPE_2__ {int w; scalar_t__ opsz; int adrmode0; int line; } ;

/* Variables and functions */
 int MODE_AN ; 
 TYPE_1__ d ; 
 int /*<<< orphan*/  desa_dn_ae (char) ; 

__attribute__((used)) static int check_desa_add_sub(void)
{
  int modemsk = !(d.w&0400) ? 07777 : 00774;
  if(d.opsz==0)	/* Fordib An for byte access size */
    modemsk &= ~(1<<MODE_AN);
  if(!(modemsk & (1<<d.adrmode0)))
    return 0;
  desa_dn_ae (d.line==0xD ? 'ADD' : 'SUB');
  return 1;
}