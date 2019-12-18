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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  MP3FreeDecoder (scalar_t__) ; 
 scalar_t__ MP3InitDecoder () ; 
 scalar_t__ mp3dec ; 

int mp3dec_start(FILE *f, int fpos_start)
{
	// must re-init decoder for new track
	if (mp3dec)
		MP3FreeDecoder(mp3dec);
	mp3dec = MP3InitDecoder();

	return (mp3dec == 0) ? -1 : 0;
}