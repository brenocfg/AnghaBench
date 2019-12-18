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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  huff_ncode; TYPE_1__* huff_buffer; } ;
struct TYPE_4__ {int code; int /*<<< orphan*/  table_id; } ;
typedef  TYPE_1__ MJpegHuffmanCode ;
typedef  TYPE_2__ MJpegContext ;

/* Variables and functions */

__attribute__((used)) static inline void ff_mjpeg_encode_code(MJpegContext *s, uint8_t table_id, int code)
{
    MJpegHuffmanCode *c = &s->huff_buffer[s->huff_ncode++];
    c->table_id = table_id;
    c->code = code;
}