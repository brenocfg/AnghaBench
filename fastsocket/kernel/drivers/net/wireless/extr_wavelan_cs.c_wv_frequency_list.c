#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_short ;
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_3__ {int i; long m; int e; } ;
typedef  TYPE_1__ iw_freq ;

/* Variables and functions */
 int* channel_bands ; 
 int /*<<< orphan*/  fee_read (int /*<<< orphan*/ ,int,int*,int) ; 

__attribute__((used)) static int
wv_frequency_list(u_long	base,	/* i/o port of the card */
		  iw_freq *	list,	/* List of frequency to fill */
		  int		max)	/* Maximum number of frequencies */
{
  u_short	table[10];	/* Authorized frequency table */
  long		freq = 0L;	/* offset to 2.4 GHz in .5 MHz + 12 MHz */
  int		i;		/* index in the table */
  const int	BAND_NUM = 10;	/* Number of bands */
  int		c = 0;		/* Channel number */

  /* Read the frequency table */
  fee_read(base, 0x71 /* frequency table */,
	   table, 10);

  /* Look all frequencies */
  i = 0;
  for(freq = 0; freq < 150; freq++)
    /* Look in the table if the frequency is allowed */
    if(table[9 - (freq / 16)] & (1 << (freq % 16)))
      {
	/* Compute approximate channel number */
	while((((channel_bands[c] >> 1) - 24) < freq) &&
	      (c < BAND_NUM))
	  c++;
	list[i].i = c;	/* Set the list index */

	/* put in the list */
	list[i].m = (((freq + 24) * 5) + 24000L) * 10000;
	list[i++].e = 1;

	/* Check number */
	if(i >= max)
	  return(i);
      }

  return(i);
}