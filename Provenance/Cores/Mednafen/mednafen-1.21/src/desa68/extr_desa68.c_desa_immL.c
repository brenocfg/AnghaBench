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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int flags; unsigned int immsym_min; unsigned int immsym_max; } ;

/* Variables and functions */
 int DESA68_SYMBOL_FLAG ; 
 TYPE_1__ d ; 
 int /*<<< orphan*/  desa_ascii (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  desa_char (char) ; 
 scalar_t__ desa_isascii (unsigned int) ; 
 int /*<<< orphan*/  desa_label (unsigned int) ; 
 int /*<<< orphan*/  desa_signifiant (int) ; 
 int /*<<< orphan*/  update_ea (unsigned int) ; 

__attribute__((used)) static void desa_immL(int v)
{
  unsigned int v2 = v;
  desa_char('#');
  if ((d.flags&DESA68_SYMBOL_FLAG) && v2>=d.immsym_min && v2<d.immsym_max) {
    desa_label(v2);
    update_ea(v2);
  } else {
    if(desa_isascii(v2) && desa_isascii(v2>>8) && desa_isascii(v2>>16) && desa_isascii(v2>>24)) {
      desa_char ('\'');
      desa_ascii((u32)v2);
      desa_char ('\'');
    } else {
      desa_signifiant(v);
    }
  }
}