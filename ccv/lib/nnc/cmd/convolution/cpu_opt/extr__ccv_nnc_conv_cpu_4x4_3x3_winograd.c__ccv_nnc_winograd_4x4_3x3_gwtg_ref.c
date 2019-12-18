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

__attribute__((used)) inline static void _ccv_nnc_winograd_4x4_3x3_gwtg_ref(const float* const w, const int c, float* gwtg)
{
	int i;
	for (i = 0; i < c; i++)
	{
		float g[18];
		/*
		 * a0, b1, c2
		 * d3, e4, f5
		 * g6, h7, i8
		 * {{a/4, b/4, c/4},
		 * {1/6 (-a - d - g), 1/6 (-b - e - h), 1/6 (-c - f - i)},
		 * {1/6 (-a + d - g), 1/6 (-b + e - h), 1/6 (-c + f - i)},
		 * {1/24 (a + 2 d + 4 g), 1/24 (b + 2 e + 4 h), 1/24 (c + 2 f + 4 i)},
		 * {1/24 (a - 2 d + 4 g), 1/24 (b - 2 e + 4 h), 1/24 (c - 2 f + 4 i)},
		 * {g, h, i}}
		 */
		/* row 1 */
		g[0] = w[i] / 4;
		g[1] = w[c + i] / 4;
		g[2] = w[2 * c + i] / 4;
		/* row 2 */
		g[3] = -(w[i] + w[3 * c + i] + w[6 * c + i]) / 6;
		g[4] = -(w[c + i] + w[4 * c + i] + w[7 * c + i]) / 6;
		g[5] = -(w[2 * c + i] + w[5 * c + i] + w[8 * c + i]) / 6;
		/* row 3 */
		g[6] = (-w[i] + w[3 * c + i] - w[6 * c + i]) / 6;
		g[7] = (-w[c + i] + w[4 * c + i] - w[7 * c + i]) / 6;
		g[8] = (-w[2 * c + i] + w[5 * c + i] - w[8 * c + i]) / 6;
		/* row 4 */
		g[9] = (w[i] + 2 * w[3 * c + i] + 4 * w[6 * c + i]) / 24;
		g[10] = (w[c + i] + 2 * w[4 * c + i] + 4 * w[7 * c + i]) / 24;
		g[11] = (w[2 * c + i] + 2 * w[5 * c + i] + 4 * w[8 * c + i]) / 24;
		/* row 5 */
		g[12] = (w[i] - 2 * w[3 * c + i] + 4 * w[6 * c + i]) / 24;
		g[13] = (w[c + i] - 2 * w[4 * c + i] + 4 * w[7 * c + i]) / 24;
		g[14] = (w[2 * c + i] - 2 * w[5 * c + i] + 4 * w[8 * c + i]) / 24;
		/* row 6 */
		g[15] = w[6 * c + i];
		g[16] = w[7 * c + i];
		g[17] = w[8 * c + i];
		/*
		 * a0, b1, c2
		 * d3, e4, f5
		 * g6, h7, i8
		 * j9, k10,l11
		 * m12,n13,o14
		 * p15,q16,r17
		 * {{a/4, 1/6 (-a - b - c), 1/6 (-a + b - c), 1/24 (a + 2 b + 4 c), 1/24 (a - 2 b + 4 c), c},
		 * {d/4, 1/6 (-d - e - f), 1/6 (-d + e - f), 1/24 (d + 2 e + 4 f), 1/24 (d - 2 e + 4 f), f},
		 * {g/4, 1/6 (-g - h - i), 1/6 (-g + h - i), 1/24 (g + 2 h + 4 i), 1/24 (g - 2 h + 4 i), i},
		 * {j/4, 1/6 (-j - k - l), 1/6 (-j + k - l), 1/24 (j + 2 k + 4 l), 1/24 (j - 2 k + 4 l), l},
		 * {m/4, 1/6 (-m - n - o), 1/6 (-m + n - o), 1/24 (m + 2 n + 4 o), 1/24 (m - 2 n + 4 o), o},
		 * {p/4, 1/6 (-p - q - r), 1/6 (-p + q - r), 1/24 (p + 2 q + 4 r), 1/24 (p - 2 q + 4 r), r}}
		 */
		/* row 1 */
		gwtg[0] = g[0] / 4;
		gwtg[c] = -(g[0] + g[1] + g[2]) / 6;
		gwtg[2 * c] = (-g[0] + g[1] - g[2]) / 6;
		gwtg[3 * c] = (g[0] + 2 * g[1] + 4 * g[2]) / 24;
		gwtg[4 * c] = (g[0] - 2 * g[1] + 4 * g[2]) / 24;
		gwtg[5 * c] = g[2];
		/* row 2 */
		gwtg[6 * c] = g[3] / 4;
		gwtg[7 * c] = -(g[3] + g[4] + g[5]) / 6;
		gwtg[8 * c] = (-g[3] + g[4] - g[5]) / 6;
		gwtg[9 * c] = (g[3] + 2 * g[4] + 4 * g[5]) / 24;
		gwtg[10 * c] = (g[3] - 2 * g[4] + 4 * g[5]) / 24;
		gwtg[11 * c] = g[5];
		/* row 3 */
		gwtg[12 * c] = g[6] / 4;
		gwtg[13 * c] = -(g[6] + g[7] + g[8]) / 6;
		gwtg[14 * c] = (-g[6] + g[7] - g[8]) / 6;
		gwtg[15 * c] = (g[6] + 2 * g[7] + 4 * g[8]) / 24;
		gwtg[16 * c] = (g[6] - 2 * g[7] + 4 * g[8]) / 24;
		gwtg[17 * c] = g[8];
		/* row 4 */
		gwtg[18 * c] = g[9] / 4;
		gwtg[19 * c] = -(g[9] + g[10] + g[11]) / 6;
		gwtg[20 * c] = (-g[9] + g[10] - g[11]) / 6;
		gwtg[21 * c] = (g[9] + 2 * g[10] + 4 * g[11]) / 24;
		gwtg[22 * c] = (g[9] - 2 * g[10] + 4 * g[11]) / 24;
		gwtg[23 * c] = g[11];
		/* row 5 */
		gwtg[24 * c] = g[12] / 4;
		gwtg[25 * c] = -(g[12] + g[13] + g[14]) / 6;
		gwtg[26 * c] = (-g[12] + g[13] - g[14]) / 6;
		gwtg[27 * c] = (g[12] + 2 * g[13] + 4 * g[14]) / 24;
		gwtg[28 * c] = (g[12] - 2 * g[13] + 4 * g[14]) / 24;
		gwtg[29 * c] = g[14];
		/* row 6 */
		gwtg[30 * c] = g[15] / 4;
		gwtg[31 * c] = -(g[15] + g[16] + g[17]) / 6;
		gwtg[32 * c] = (-g[15] + g[16] - g[17]) / 6;
		gwtg[33 * c] = (g[15] + 2 * g[16] + 4 * g[17]) / 24;
		gwtg[34 * c] = (g[15] - 2 * g[16] + 4 * g[17]) / 24;
		gwtg[35 * c] = g[17];
		++gwtg;
	}
}