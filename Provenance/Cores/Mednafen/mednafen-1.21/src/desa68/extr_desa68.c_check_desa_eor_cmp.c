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
struct TYPE_2__ {int opsz; int w; int adrmode0; } ;

/* Variables and functions */
 TYPE_1__ d ; 
 int /*<<< orphan*/  desa_dn_ae (int) ; 

__attribute__((used)) static int check_desa_eor_cmp()
{
  int modemsk, inst;

  if(d.opsz==3)
    return 0;

  /* EOR */
  else if(d.w&0400)
    {
      modemsk = 00775;
      inst = 'EOR';
    }

  /* CMP */
  else
    {
      modemsk = (!d.opsz) ? 07775 : 07777;
      inst = 'CMP';
    }

  if(!(modemsk&(1<<d.adrmode0)))
    return 0;

  desa_dn_ae(inst);
  return 1;
}