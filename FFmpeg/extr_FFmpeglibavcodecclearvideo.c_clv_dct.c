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
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  COP ; 
 int /*<<< orphan*/  DCT_TEMPLATE (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ROP ; 

__attribute__((used)) static void clv_dct(int16_t *block)
{
    int i;
    int16_t *ptr;

    ptr = block;
    for (i = 0; i < 8; i++) {
        DCT_TEMPLATE(ptr, 1, 0x80, 8, 11, ROP);
        ptr += 8;
    }

    ptr = block;
    for (i = 0; i < 8; i++) {
        DCT_TEMPLATE(ptr, 8, 0x2000, 14, 8, COP);
        ptr++;
    }
}