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
struct TYPE_3__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ FFBufferRef ;

/* Variables and functions */
 int /*<<< orphan*/  av_free (TYPE_1__*) ; 
 int /*<<< orphan*/  ffmmal_poolref_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmal_buffer_header_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ffmmal_release_frame(void *opaque, uint8_t *data)
{
    FFBufferRef *ref = (void *)data;

    mmal_buffer_header_release(ref->buffer);
    ffmmal_poolref_unref(ref->pool);

    av_free(ref);
}