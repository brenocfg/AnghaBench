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
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_3__ {unsigned int (* scalarproduct_int16 ) (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ AudioDSPContext ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCKSIZE ; 
 int ff_t_sqrt (unsigned int) ; 
 unsigned int stub1 (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

int ff_irms(AudioDSPContext *adsp, const int16_t *data)
{
    unsigned int sum = adsp->scalarproduct_int16(data, data, BLOCKSIZE);

    if (sum == 0)
        return 0; /* OOPS - division by zero */

    return 0x20000000 / (ff_t_sqrt(sum) >> 8);
}