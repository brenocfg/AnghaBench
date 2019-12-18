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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ptrdiff_t ;
typedef  int int16_t ;
typedef  int FLOAT ;

/* Variables and functions */
 int /*<<< orphan*/  emms_c () ; 
 int /*<<< orphan*/  p8idct (int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int* prescale ; 

void ff_faanidct_add(uint8_t *dest, ptrdiff_t line_size, int16_t block[64])
{
    FLOAT temp[64];
    int i;

    emms_c();

    for(i=0; i<64; i++)
        temp[i] = block[i] * prescale[i];

    p8idct(block, temp, NULL,         0, 1, 8, 0);
    p8idct(NULL , temp, dest, line_size, 8, 1, 2);
}