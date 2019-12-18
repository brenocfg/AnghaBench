#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/ * samples; } ;
typedef  TYPE_1__ rwav_t ;
struct TYPE_6__ {size_t size; int /*<<< orphan*/  step; int /*<<< orphan*/  const* data; TYPE_1__* out; } ;
typedef  TYPE_2__ rwav_iterator_t ;

/* Variables and functions */
 int /*<<< orphan*/  ITER_BEGIN ; 

void rwav_init(rwav_iterator_t* iter, rwav_t* out, const void* buf, size_t size)
{
   iter->out    = out;
   iter->data   = (const uint8_t*)buf;
   iter->size   = size;
   iter->step   = ITER_BEGIN;

   out->samples = NULL;
}