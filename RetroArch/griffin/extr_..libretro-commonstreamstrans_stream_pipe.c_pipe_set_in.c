#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct pipe_trans_stream {int /*<<< orphan*/  in_size; int /*<<< orphan*/  const* in; } ;

/* Variables and functions */

__attribute__((used)) static void pipe_set_in(void *data, const uint8_t *in, uint32_t in_size)
{
   struct pipe_trans_stream *p = (struct pipe_trans_stream *) data;
   p->in = in;
   p->in_size = in_size;
}