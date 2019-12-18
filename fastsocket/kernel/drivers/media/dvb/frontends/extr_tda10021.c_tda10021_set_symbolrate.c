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
typedef  int u32 ;
typedef  int u16 ;
struct tda10021_state {int dummy; } ;
typedef  int s32 ;
typedef  int s16 ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (int,int) ; 
 int FIN ; 
 int XIN ; 
 int /*<<< orphan*/  _tda10021_writereg (struct tda10021_state*,int,int) ; 
 int* tda10021_inittab ; 

__attribute__((used)) static int tda10021_set_symbolrate (struct tda10021_state* state, u32 symbolrate)
{
	s32 BDR;
	s32 BDRI;
	s16 SFIL=0;
	u16 NDEC = 0;
	u32 tmp, ratio;

	if (symbolrate > XIN/2)
		symbolrate = XIN/2;
	if (symbolrate < 500000)
		symbolrate = 500000;

	if (symbolrate < XIN/16) NDEC = 1;
	if (symbolrate < XIN/32) NDEC = 2;
	if (symbolrate < XIN/64) NDEC = 3;

	if (symbolrate < (u32)(XIN/12.3)) SFIL = 1;
	if (symbolrate < (u32)(XIN/16))	 SFIL = 0;
	if (symbolrate < (u32)(XIN/24.6)) SFIL = 1;
	if (symbolrate < (u32)(XIN/32))	 SFIL = 0;
	if (symbolrate < (u32)(XIN/49.2)) SFIL = 1;
	if (symbolrate < (u32)(XIN/64))	 SFIL = 0;
	if (symbolrate < (u32)(XIN/98.4)) SFIL = 1;

	symbolrate <<= NDEC;
	ratio = (symbolrate << 4) / FIN;
	tmp =  ((symbolrate << 4) % FIN) << 8;
	ratio = (ratio << 8) + tmp / FIN;
	tmp = (tmp % FIN) << 8;
	ratio = (ratio << 8) + DIV_ROUND_CLOSEST(tmp, FIN);

	BDR = ratio;
	BDRI = (((XIN << 5) / symbolrate) + 1) / 2;

	if (BDRI > 0xFF)
		BDRI = 0xFF;

	SFIL = (SFIL << 4) | tda10021_inittab[0x0E];

	NDEC = (NDEC << 6) | tda10021_inittab[0x03];

	_tda10021_writereg (state, 0x03, NDEC);
	_tda10021_writereg (state, 0x0a, BDR&0xff);
	_tda10021_writereg (state, 0x0b, (BDR>> 8)&0xff);
	_tda10021_writereg (state, 0x0c, (BDR>>16)&0x3f);

	_tda10021_writereg (state, 0x0d, BDRI);
	_tda10021_writereg (state, 0x0e, SFIL);

	return 0;
}