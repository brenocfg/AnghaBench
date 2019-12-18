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
 scalar_t__ Configuration2 ; 
 int FIFO_Size ; 
 scalar_t__ IO_Control ; 
 scalar_t__ LSB_ID_Code ; 
 scalar_t__ MSB_ID_Code ; 
 int /*<<< orphan*/  chip ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,int,int) ; 
 int /*<<< orphan*/  tmc1800 ; 
 int /*<<< orphan*/  tmc18c30 ; 
 int /*<<< orphan*/  tmc18c50 ; 

__attribute__((used)) static int fdomain_is_valid_port( int port )
{
#if DEBUG_DETECT 
   printk( " (%x%x),",
	   inb( port + MSB_ID_Code ), inb( port + LSB_ID_Code ) );
#endif

   /* The MCA ID is a unique id for each MCA compatible board.  We
      are using ISA boards, but Future Domain provides the MCA ID
      anyway.  We can use this ID to ensure that this is a Future
      Domain TMC-1660/TMC-1680.
    */

   if (inb( port + LSB_ID_Code ) != 0xe9) { /* test for 0x6127 id */
      if (inb( port + LSB_ID_Code ) != 0x27) return 0;
      if (inb( port + MSB_ID_Code ) != 0x61) return 0;
      chip = tmc1800;
   } else {				    /* test for 0xe960 id */
      if (inb( port + MSB_ID_Code ) != 0x60) return 0;
      chip = tmc18c50;

				/* Try to toggle 32-bit mode.  This only
				   works on an 18c30 chip.  (User reports
				   say this works, so we should switch to
				   it in the near future.) */

      outb( 0x80, port + IO_Control );
      if ((inb( port + Configuration2 ) & 0x80) == 0x80) {
	 outb( 0x00, port + IO_Control );
	 if ((inb( port + Configuration2 ) & 0x80) == 0x00) {
	    chip = tmc18c30;
	    FIFO_Size = 0x800;	/* 2k FIFO */
	 }
      }
				/* If that failed, we are an 18c50. */
   }

   return 1;
}