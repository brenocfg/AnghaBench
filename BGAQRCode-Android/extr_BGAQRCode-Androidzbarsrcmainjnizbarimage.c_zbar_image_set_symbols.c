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
typedef  int /*<<< orphan*/  const zbar_symbol_set_t ;
struct TYPE_3__ {int /*<<< orphan*/  const* syms; } ;
typedef  TYPE_1__ zbar_image_t ;

/* Variables and functions */
 int /*<<< orphan*/  zbar_symbol_set_ref (int /*<<< orphan*/  const*,int) ; 

void zbar_image_set_symbols (zbar_image_t *img,
                             const zbar_symbol_set_t *syms)
{
    if(syms)
        zbar_symbol_set_ref(syms, 1);
    if(img->syms)
        zbar_symbol_set_ref(img->syms, -1);
    img->syms = (zbar_symbol_set_t*)syms;
}