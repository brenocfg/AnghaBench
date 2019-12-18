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
 int /*<<< orphan*/  CPU_ClrN ; 
 int CPU_regA ; 
 int CPU_regY ; 
 int /*<<< orphan*/  DBG_APRINT (char*) ; 
 int /*<<< orphan*/  Devices_ICAX1Z ; 
 int /*<<< orphan*/  Devices_ICAX2Z ; 
 int /*<<< orphan*/  Devices_ICDNOZ ; 
 int MEMORY_dGetByte (int /*<<< orphan*/ ) ; 
 int Peek (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDevice_GetInetAddress () ; 
 scalar_t__ RDevice_serial_enabled ; 
 scalar_t__ bufend ; 
 int /*<<< orphan*/  inetaddress ; 
 int /*<<< orphan*/  open_connection (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  open_connection_serial (int) ; 

void RDevice_OPEN(void)
{
  int  port;
  int  direction;
  int  devnum;

  CPU_regA = 1;
  CPU_regY = 1;
  CPU_ClrN;

  bufend = 0;

  port = Peek(Devices_ICAX2Z);
  direction = Peek(Devices_ICAX1Z);
  devnum = MEMORY_dGetByte(Devices_ICDNOZ);
  if(direction & 0x04)
  {
    DBG_APRINT("R*: Open for Reading...");
  }

  if(direction & 0x08)
  {
    DBG_APRINT("R*: Open for Writing...");
#ifdef R_SERIAL
    if(RDevice_serial_enabled)
    {
      DBG_APRINT("R*: serial mode.");
      open_connection_serial(devnum);
    }
#endif /* R_SERIAL */
#if defined(R_SERIAL) && defined(R_NETWORK)
    else
#endif
#ifdef R_NETWORK
    {
      DBG_APRINT("R*: Socket mode.");
      RDevice_GetInetAddress();
      open_connection(inetaddress, port);
    }
#endif /* R_NETWORK */
  }
  if(direction & 0x01)
  {
    /* Open for concurrent mode */
  }

}