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
struct TYPE_4__ {int /*<<< orphan*/  num_rows; int /*<<< orphan*/  xbits; } ;
typedef  TYPE_1__ IVIHuffDesc ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ivi_huff_desc_copy(IVIHuffDesc *dst, const IVIHuffDesc *src)
{
    dst->num_rows = src->num_rows;
    memcpy(dst->xbits, src->xbits, src->num_rows);
}