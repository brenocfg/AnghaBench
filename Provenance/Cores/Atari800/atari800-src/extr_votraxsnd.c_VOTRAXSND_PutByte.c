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
typedef  int UBYTE ;

/* Variables and functions */
 scalar_t__ PBI_XLD_enabled ; 
 int /*<<< orphan*/  PBI_XLD_votrax_busy_callback (void*) ; 
 void* TRUE ; 
 void* VOTRAXSND_busy ; 
 scalar_t__ Votrax_Samples (int,int,int) ; 
 double ratio ; 
 int votrax_sync_samples ; 
 void* votrax_written ; 
 int votrax_written_byte ; 

void VOTRAXSND_PutByte(UBYTE byte)
{
	/* put byte to voice box */
	votrax_sync_samples = (int)((1.0/ratio)*(double)Votrax_Samples((votrax_written_byte&0x3f), (byte&0x3f), votrax_sync_samples));
	votrax_written = TRUE;
	votrax_written_byte = byte;
	if (!VOTRAXSND_busy) {
		VOTRAXSND_busy = TRUE;
#ifdef PBI_XLD
		if (PBI_XLD_enabled) {
			PBI_XLD_votrax_busy_callback(TRUE); /* idle -> busy */
		}
#endif
	}
}