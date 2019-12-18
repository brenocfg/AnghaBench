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
 int /*<<< orphan*/  isdn_audio_alaw_to_ulaw ; 
 int /*<<< orphan*/  isdn_audio_tlookup (int /*<<< orphan*/ ,unsigned char*,unsigned long) ; 

void
isdn_audio_alaw2ulaw(unsigned char *buff, unsigned long len)
{
	isdn_audio_tlookup(isdn_audio_alaw_to_ulaw, buff, len);
}