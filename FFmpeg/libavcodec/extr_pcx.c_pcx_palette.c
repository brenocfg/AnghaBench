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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  GetByteContext ;

/* Variables and functions */
 int FFMIN (int,int) ; 
 int bytestream2_get_be24u (int /*<<< orphan*/ *) ; 
 int bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pcx_palette(GetByteContext *gb, uint32_t *dst, int pallen)
{
    int i;

    pallen = FFMIN(pallen, bytestream2_get_bytes_left(gb) / 3);
    for (i = 0; i < pallen; i++)
        *dst++ = 0xFF000000 | bytestream2_get_be24u(gb);
    if (pallen < 256)
        memset(dst, 0, (256 - pallen) * sizeof(*dst));
}