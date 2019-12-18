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
struct snd_info_buffer {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int SND_PRINT_BITS_ADVISED_BUFSIZE ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 
 int /*<<< orphan*/  snd_print_pcm_bits (unsigned int,char*,int) ; 

__attribute__((used)) static void print_pcm_bits(struct snd_info_buffer *buffer, unsigned int pcm)
{
	char buf[SND_PRINT_BITS_ADVISED_BUFSIZE];

	snd_iprintf(buffer, "    bits [0x%x]:", (pcm >> 16) & 0xff);
	snd_print_pcm_bits(pcm, buf, sizeof(buf));
	snd_iprintf(buffer, "%s\n", buf);
}