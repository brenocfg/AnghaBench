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
typedef  int /*<<< orphan*/  UBYTE ;
typedef  int /*<<< orphan*/  SWORD ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int VTRX_BLOCK_SIZE ; 
 int /*<<< orphan*/  Votrax_PutByte (int /*<<< orphan*/ ) ; 
 scalar_t__ bit16 ; 
 int /*<<< orphan*/  mix (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mix8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int num_pokeys ; 
 int /*<<< orphan*/  temp_votrax_buffer ; 
 int /*<<< orphan*/  votrax_buffer ; 
 int /*<<< orphan*/  votrax_process (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ votrax_written ; 
 int /*<<< orphan*/  votrax_written_byte ; 
 int /*<<< orphan*/  votraxsnd_enabled () ; 

void VOTRAXSND_Process(void *sndbuffer, int sndn)
{
	if (!votraxsnd_enabled()) return;

	if(votrax_written) {
		votrax_written = FALSE;
		Votrax_PutByte(votrax_written_byte);
	}
	sndn /= num_pokeys;
	while (sndn > 0) {
		int amount = ((sndn > VTRX_BLOCK_SIZE) ? VTRX_BLOCK_SIZE : sndn);
		votrax_process(votrax_buffer, amount, temp_votrax_buffer);
		if (bit16) mix((SWORD *)sndbuffer, votrax_buffer, amount, 128/4);
		else mix8((UBYTE *)sndbuffer, votrax_buffer, amount, 128/4);
		sndbuffer = (char *) sndbuffer + VTRX_BLOCK_SIZE*(bit16 ? 2 : 1)*((num_pokeys == 2) ? 2: 1);
		sndn -= VTRX_BLOCK_SIZE;
	}
}