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
struct TYPE_3__ {int* w; unsigned char idx; } ;
typedef  TYPE_1__ zbar_decoder_t ;

/* Variables and functions */
 int DECODE_WINDOW ; 

__attribute__((used)) static inline unsigned get_width (const zbar_decoder_t *dcode,
                                  unsigned char offset)
{
    return(dcode->w[(dcode->idx - offset) & (DECODE_WINDOW - 1)]);
}