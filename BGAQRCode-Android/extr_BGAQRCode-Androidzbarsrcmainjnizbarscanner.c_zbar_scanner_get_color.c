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
struct TYPE_3__ {scalar_t__ y1_sign; } ;
typedef  TYPE_1__ zbar_scanner_t ;
typedef  int /*<<< orphan*/  zbar_color_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZBAR_BAR ; 
 int /*<<< orphan*/  ZBAR_SPACE ; 

zbar_color_t zbar_scanner_get_color (const zbar_scanner_t *scn)
{
    return((scn->y1_sign <= 0) ? ZBAR_SPACE : ZBAR_BAR);
}