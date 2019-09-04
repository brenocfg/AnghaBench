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
typedef  int ptrdiff_t ;
typedef  int int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  IDCT_ROW (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ea_idct_col (int*,int*) ; 

void ff_ea_idct_put_c(uint8_t *dest, ptrdiff_t linesize, int16_t *block)
{
    int i;
    int16_t temp[64];
    block[0] += 4;
    for (i=0; i<8; i++)
        ea_idct_col(&temp[i], &block[i]);
    for (i=0; i<8; i++)
        IDCT_ROW( (&dest[i*linesize]), (&temp[8*i]) );
}