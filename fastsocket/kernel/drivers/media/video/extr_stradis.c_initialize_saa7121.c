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
typedef  int u8 ;
struct saa7146 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2CWrite (struct saa7146*,int,int,int,int) ; 
 int INIT7121LEN ; 
 int NTSCFirstActive ; 
 int NTSCLastActive ; 
 scalar_t__ NewCard ; 
 int PALFirstActive ; 
 int PALLastActive ; 
 int /*<<< orphan*/  SAA7146_PSR ; 
 int* init7121ntsc ; 
 int* init7121pal ; 
 int saaread (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void initialize_saa7121(struct saa7146 *saa, int dopal)
{
	int i, mod;
	u8 *sequence;
	if (dopal)
		sequence = init7121pal;
	else
		sequence = init7121ntsc;
	mod = saaread(SAA7146_PSR) & 0x08;
	/* initialize PAL/NTSC video encoder */
	for (i = 0; i < INIT7121LEN; i++) {
		if (NewCard) {	/* handle new card encoder differences */
			if (sequence[i * 2] == 0x3a)
				I2CWrite(saa, 0x88, 0x3a, 0x13, 2);
			else if (sequence[i * 2] == 0x6b)
				I2CWrite(saa, 0x88, 0x6b, 0x20, 2);
			else if (sequence[i * 2] == 0x6c)
				I2CWrite(saa, 0x88, 0x6c,
					 dopal ? 0x09 : 0xf5, 2);
			else if (sequence[i * 2] == 0x6d)
				I2CWrite(saa, 0x88, 0x6d,
					 dopal ? 0x20 : 0x00, 2);
			else if (sequence[i * 2] == 0x7a)
				I2CWrite(saa, 0x88, 0x7a,
					 dopal ? (PALFirstActive - 1) :
					 (NTSCFirstActive - 4), 2);
			else if (sequence[i * 2] == 0x7b)
				I2CWrite(saa, 0x88, 0x7b,
					 dopal ? PALLastActive :
					 NTSCLastActive, 2);
			else
				I2CWrite(saa, 0x88, sequence[i * 2],
					 sequence[i * 2 + 1], 2);
		} else {
			if (sequence[i * 2] == 0x6b && mod)
				I2CWrite(saa, 0x88, 0x6b,
					 (sequence[i * 2 + 1] ^ 0x09), 2);
			else if (sequence[i * 2] == 0x7a)
				I2CWrite(saa, 0x88, 0x7a,
					 dopal ? (PALFirstActive - 1) :
					 (NTSCFirstActive - 4), 2);
			else if (sequence[i * 2] == 0x7b)
				I2CWrite(saa, 0x88, 0x7b,
					 dopal ? PALLastActive :
					 NTSCLastActive, 2);
			else
				I2CWrite(saa, 0x88, sequence[i * 2],
					 sequence[i * 2 + 1], 2);
		}
	}
}