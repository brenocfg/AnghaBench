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
struct TYPE_3__ {size_t bpf_pc; int /*<<< orphan*/  cur_ip; int /*<<< orphan*/ * refs; } ;
typedef  TYPE_1__ binary_stream ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  scalar_t__ UINT ;

/* Variables and functions */

void emit_length(binary_stream *stream, ULONG value, UINT len)
{
	(stream->refs)[stream->bpf_pc]+=len;
	stream->cur_ip+=len;
}