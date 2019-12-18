#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 scalar_t__ ALTIVEC_REGNO_P (unsigned int) ; 
 unsigned int COUNT_REGISTER_REGNUM ; 
 unsigned int CR0_REGNO ; 
 scalar_t__ CR_REGNO_P (unsigned int) ; 
 scalar_t__ DWARF2_DEBUG ; 
 unsigned int FIRST_ALTIVEC_REGNO ; 
 unsigned int LINK_REGISTER_REGNUM ; 
 unsigned int MQ_REGNO ; 
 unsigned int SPEFSCR_REGNO ; 
 unsigned int SPE_ACC_REGNO ; 
 unsigned int VRSAVE_REGNO ; 
 unsigned int VSCR_REGNO ; 
 unsigned int XER_REGNO ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ write_symbols ; 

unsigned int
rs6000_dbx_register_number (unsigned int regno)
{
  if (regno <= 63 || write_symbols != DWARF2_DEBUG)
    return regno;
  if (regno == MQ_REGNO)
    return 100;
  if (regno == LINK_REGISTER_REGNUM)
    return 108;
  if (regno == COUNT_REGISTER_REGNUM)
    return 109;
  if (CR_REGNO_P (regno))
    return regno - CR0_REGNO + 86;
  if (regno == XER_REGNO)
    return 101;
  if (ALTIVEC_REGNO_P (regno))
    return regno - FIRST_ALTIVEC_REGNO + 1124;
  if (regno == VRSAVE_REGNO)
    return 356;
  if (regno == VSCR_REGNO)
    return 67;
  if (regno == SPE_ACC_REGNO)
    return 99;
  if (regno == SPEFSCR_REGNO)
    return 612;
  /* SPE high reg number.  We get these values of regno from
     rs6000_dwarf_register_span.  */
  gcc_assert (regno >= 1200 && regno < 1232);
  return regno;
}