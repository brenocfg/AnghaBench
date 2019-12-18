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
struct TYPE_3__ {struct TYPE_3__* description; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ ID3v2ExtraMetaAPIC ;

/* Variables and functions */
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (TYPE_1__**) ; 

__attribute__((used)) static void free_apic(void *obj)
{
    ID3v2ExtraMetaAPIC *apic = obj;
    av_buffer_unref(&apic->buf);
    av_freep(&apic->description);
    av_freep(&apic);
}