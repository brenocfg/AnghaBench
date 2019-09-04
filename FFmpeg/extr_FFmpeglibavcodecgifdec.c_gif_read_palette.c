#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ GifState ;

/* Variables and functions */
 int bytestream2_get_be24u (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gif_read_palette(GifState *s, uint32_t *pal, int nb)
{
    int i;

    for (i = 0; i < nb; i++, pal++)
        *pal = (0xffu << 24) | bytestream2_get_be24u(&s->gb);
}