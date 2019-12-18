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
struct net_device {int dummy; } ;

/* Variables and functions */
 unsigned char HIBYTE (unsigned short) ; 
 unsigned char LOBYTE (unsigned short) ; 
 int /*<<< orphan*/  SIFADR ; 
 int /*<<< orphan*/  SIFADX ; 
 int /*<<< orphan*/  SIFINC ; 
 unsigned short SIFREADW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIFWRITEW (unsigned short,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tms380tr_read_ram(struct net_device *dev, unsigned char *Data,
				unsigned short Address, int Length)
{
	int i;
	unsigned short old_sifadx, old_sifadr, InWord;

	/* Save the current values */
	old_sifadx = SIFREADW(SIFADX);
	old_sifadr = SIFREADW(SIFADR);

	/* Page number of adapter memory */
	SIFWRITEW(0x0001, SIFADX);
	/* Address offset in adapter RAM */
        SIFWRITEW(Address, SIFADR);

	/* Copy len byte from adapter memory to system data area. */
	i = 0;
	for(;;)
	{
		InWord = SIFREADW(SIFINC);

		*(Data + i) = HIBYTE(InWord);	/* Write first byte */
		if(++i == Length)		/* All is done break */
			break;

		*(Data + i) = LOBYTE(InWord);	/* Write second byte */
		if (++i == Length)		/* All is done break */
			break;
	}

	/* Restore original values */
	SIFWRITEW(old_sifadx, SIFADX);
	SIFWRITEW(old_sifadr, SIFADR);

	return;
}