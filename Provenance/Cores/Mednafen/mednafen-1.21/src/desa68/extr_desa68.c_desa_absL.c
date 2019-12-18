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
struct TYPE_2__ {int flags; unsigned int immsym_min; unsigned int immsym_max; } ;

/* Variables and functions */
 int DESA68_SYMBOL_FLAG ; 
 TYPE_1__ d ; 
 int /*<<< orphan*/  desa_str (char*) ; 
 int /*<<< orphan*/  desa_uhexacat (unsigned int,int,char) ; 
 int /*<<< orphan*/  desa_usignifiant (int) ; 

__attribute__((used)) static void desa_absL(int v)
{
  unsigned int v2 = v & 0xFFFFFF;

  if ((d.flags&DESA68_SYMBOL_FLAG) && v2>=d.immsym_min && v2<d.immsym_max) {
    desa_uhexacat(v2, 6, 'L');
  } else {
    desa_usignifiant(v);
    desa_str(".L");
  }
}