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

/* Variables and functions */
 int /*<<< orphan*/  VICAM_HEADER_SIZE ; 
 int clamp (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vicam_decode_color(const u8 *data, u8 *rgb)
{
	/* vicam_decode_color - Convert from Vicam Y-Cr-Cb to RGB
	 * Copyright (C) 2002 Monroe Williams (monroe@pobox.com)
	 */

	int i, prevY, nextY;

	prevY = 512;
	nextY = 512;

	data += VICAM_HEADER_SIZE;

	for( i = 0; i < 240; i++, data += 512 ) {
		const int y = ( i * 242 ) / 240;

		int j, prevX, nextX;
		int Y, Cr, Cb;

		if ( y == 242 - 1 ) {
			nextY = -512;
		}

		prevX = 1;
		nextX = 1;

		for ( j = 0; j < 320; j++, rgb += 3 ) {
			const int x = ( j * 512 ) / 320;
			const u8 * const src = &data[x];

			if ( x == 512 - 1 ) {
				nextX = -1;
			}

			Cr = ( src[prevX] - src[0] ) +
				( src[nextX] - src[0] );
			Cr /= 2;

			Cb = ( src[prevY] - src[prevX + prevY] ) +
				( src[prevY] - src[nextX + prevY] ) +
				( src[nextY] - src[prevX + nextY] ) +
				( src[nextY] - src[nextX + nextY] );
			Cb /= 4;

			Y = 1160 * ( src[0] + ( Cr / 2 ) - 16 );

			if ( i & 1 ) {
				int Ct = Cr;
				Cr = Cb;
				Cb = Ct;
			}

			if ( ( x ^ i ) & 1 ) {
				Cr = -Cr;
				Cb = -Cb;
			}

			rgb[0] = clamp( ( ( Y + ( 2017 * Cb ) ) +
					500 ) / 900, 0, 255 );
			rgb[1] = clamp( ( ( Y - ( 392 * Cb ) -
					  ( 813 * Cr ) ) +
					  500 ) / 1000, 0, 255 );
			rgb[2] = clamp( ( ( Y + ( 1594 * Cr ) ) +
					500 ) / 1300, 0, 255 );

			prevX = -1;
		}

		prevY = -512;
	}
}