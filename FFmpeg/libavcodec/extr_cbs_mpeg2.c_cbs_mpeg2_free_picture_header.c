#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  extra_information_ref; } ;
struct TYPE_4__ {TYPE_1__ extra_information_picture; } ;
typedef  TYPE_2__ MPEG2RawPictureHeader ;

/* Variables and functions */
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 

__attribute__((used)) static void cbs_mpeg2_free_picture_header(void *opaque, uint8_t *content)
{
    MPEG2RawPictureHeader *picture = (MPEG2RawPictureHeader*)content;
    av_buffer_unref(&picture->extra_information_picture.extra_information_ref);
    av_freep(&content);
}