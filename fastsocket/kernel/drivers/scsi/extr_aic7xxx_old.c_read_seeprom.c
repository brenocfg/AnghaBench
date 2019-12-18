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
struct aic7xxx_host {int dummy; } ;
typedef  scalar_t__ seeprom_chip_type ;
struct TYPE_2__ {int member_0; int member_1; int /*<<< orphan*/  member_2; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_PULSE (struct aic7xxx_host*) ; 
 int SEECK ; 
 int SEECS ; 
 int /*<<< orphan*/  SEECTL ; 
 unsigned short SEEDI ; 
 int SEEMS ; 
 scalar_t__ acquire_seeprom (struct aic7xxx_host*) ; 
 unsigned short aic_inb (struct aic7xxx_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aic_outb (struct aic7xxx_host*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  release_seeprom (struct aic7xxx_host*) ; 

__attribute__((used)) static int
read_seeprom(struct aic7xxx_host *p, int offset, 
    unsigned short *scarray, unsigned int len, seeprom_chip_type chip)
{
  int i = 0, k;
  unsigned char temp;
  unsigned short checksum = 0;
  struct seeprom_cmd {
    unsigned char len;
    unsigned char bits[3];
  };
  struct seeprom_cmd seeprom_read = {3, {1, 1, 0}};

  /*
   * Request access of the memory port.
   */
  if (acquire_seeprom(p) == 0)
  {
    return (0);
  }

  /*
   * Read 'len' registers of the seeprom.  For the 7870, the 93C46
   * SEEPROM is a 1024-bit device with 64 16-bit registers but only
   * the first 32 are used by Adaptec BIOS.  Some adapters use the
   * 93C56 SEEPROM which is a 2048-bit device.  The loop will range
   * from 0 to 'len' - 1.
   */
  for (k = 0; k < len; k++)
  {
    /*
     * Send chip select for one clock cycle.
     */
    aic_outb(p, SEEMS | SEECK | SEECS, SEECTL);
    CLOCK_PULSE(p);

    /*
     * Now we're ready to send the read command followed by the
     * address of the 16-bit register we want to read.
     */
    for (i = 0; i < seeprom_read.len; i++)
    {
      temp = SEEMS | SEECS | (seeprom_read.bits[i] << 1);
      aic_outb(p, temp, SEECTL);
      CLOCK_PULSE(p);
      temp = temp ^ SEECK;
      aic_outb(p, temp, SEECTL);
      CLOCK_PULSE(p);
    }
    /*
     * Send the 6 or 8 bit address (MSB first, LSB last).
     */
    for (i = ((int) chip - 1); i >= 0; i--)
    {
      temp = k + offset;
      temp = (temp >> i) & 1;  /* Mask out all but lower bit. */
      temp = SEEMS | SEECS | (temp << 1);
      aic_outb(p, temp, SEECTL);
      CLOCK_PULSE(p);
      temp = temp ^ SEECK;
      aic_outb(p, temp, SEECTL);
      CLOCK_PULSE(p);
    }

    /*
     * Now read the 16 bit register.  An initial 0 precedes the
     * register contents which begins with bit 15 (MSB) and ends
     * with bit 0 (LSB).  The initial 0 will be shifted off the
     * top of our word as we let the loop run from 0 to 16.
     */
    for (i = 0; i <= 16; i++)
    {
      temp = SEEMS | SEECS;
      aic_outb(p, temp, SEECTL);
      CLOCK_PULSE(p);
      temp = temp ^ SEECK;
      scarray[k] = (scarray[k] << 1) | (aic_inb(p, SEECTL) & SEEDI);
      aic_outb(p, temp, SEECTL);
      CLOCK_PULSE(p);
    }

    /*
     * The serial EEPROM should have a checksum in the last word.
     * Keep a running checksum for all words read except for the
     * last word.  We'll verify the checksum after all words have
     * been read.
     */
    if (k < (len - 1))
    {
      checksum = checksum + scarray[k];
    }

    /*
     * Reset the chip select for the next command cycle.
     */
    aic_outb(p, SEEMS, SEECTL);
    CLOCK_PULSE(p);
    aic_outb(p, SEEMS | SEECK, SEECTL);
    CLOCK_PULSE(p);
    aic_outb(p, SEEMS, SEECTL);
    CLOCK_PULSE(p);
  }

  /*
   * Release access to the memory port and the serial EEPROM.
   */
  release_seeprom(p);

#if 0
  printk("Computed checksum 0x%x, checksum read 0x%x\n",
         checksum, scarray[len - 1]);
  printk("Serial EEPROM:");
  for (k = 0; k < len; k++)
  {
    if (((k % 8) == 0) && (k != 0))
    {
      printk("\n              ");
    }
    printk(" 0x%x", scarray[k]);
  }
  printk("\n");
#endif
  if ( (checksum != scarray[len - 1]) || (checksum == 0) )
  {
    return (0);
  }

  return (1);
}