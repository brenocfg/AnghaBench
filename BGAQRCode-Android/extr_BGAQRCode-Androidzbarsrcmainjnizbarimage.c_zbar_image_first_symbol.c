#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zbar_symbol_t ;
struct TYPE_5__ {TYPE_1__* syms; } ;
typedef  TYPE_2__ zbar_image_t ;
struct TYPE_4__ {int /*<<< orphan*/  const* head; } ;

/* Variables and functions */

const zbar_symbol_t *zbar_image_first_symbol (const zbar_image_t *img)
{
    return((img->syms) ? img->syms->head : NULL);
}