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
struct TYPE_3__ {int /*<<< orphan*/ * gamma_lut; } ;
typedef  TYPE_1__ hb_filter_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  pow (float,float) ; 

__attribute__((used)) static void build_gamma_lut( hb_filter_private_t * pv )
{
    int i;
    for (i = 0; i < 256; i++)
    {
        pv->gamma_lut[i] = pow( ( (float)i / (float)255 ), 2.2f );
    }
}