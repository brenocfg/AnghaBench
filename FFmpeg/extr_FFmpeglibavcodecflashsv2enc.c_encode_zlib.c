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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {scalar_t__ sl_begin; scalar_t__ sl_end; } ;
typedef  TYPE_1__ Block ;

/* Variables and functions */
 int Z_OK ; 
 int compress2 (int /*<<< orphan*/ *,unsigned long*,scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static int encode_zlib(Block * b, uint8_t * buf, unsigned long *buf_size, int comp)
{
    int res = compress2(buf, buf_size, b->sl_begin, b->sl_end - b->sl_begin, comp);
    return res == Z_OK ? 0 : -1;
}