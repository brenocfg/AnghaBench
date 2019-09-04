#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zbar_symbol_set_t ;
struct TYPE_4__ {int /*<<< orphan*/ * syms; } ;
typedef  TYPE_1__ zbar_image_t ;

/* Variables and functions */

__attribute__((used)) static inline void _zbar_image_swap_symbols (zbar_image_t *a,
                                             zbar_image_t *b)
{
    zbar_symbol_set_t *tmp = a->syms;
    a->syms = b->syms;
    b->syms = tmp;
}