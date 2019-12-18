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
struct TYPE_2__ {char szchar; int w; int reg9; int /*<<< orphan*/  reg0; int /*<<< orphan*/  mode3; } ;

/* Variables and functions */
 TYPE_1__ d ; 
 int /*<<< orphan*/  desa_ascii (char) ; 
 int /*<<< orphan*/  desa_char (char) ; 
 int /*<<< orphan*/  get_ea_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static void desa_dn_ae(int name)
{
  desa_ascii(name);
  desa_ascii(d.szchar);
  desa_char (' ');
  /*  dn,<ae> */
  if(d.w&0400)
    {
      desa_ascii('D0,' + (d.reg9<<8));
      get_ea_2(d.mode3, d.reg0, d.szchar);
    }

  /*  <ae>,dn */
  else
    {
      get_ea_2(d.mode3, d.reg0, d.szchar);
      desa_ascii(',D0'+d.reg9);
    }
}