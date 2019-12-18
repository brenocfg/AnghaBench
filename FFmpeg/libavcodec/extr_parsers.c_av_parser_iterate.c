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
typedef  int /*<<< orphan*/  AVCodecParser ;

/* Variables and functions */
 int /*<<< orphan*/ ** parser_list ; 

const AVCodecParser *av_parser_iterate(void **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    const AVCodecParser *p = parser_list[i];

    if (p)
        *opaque = (void*)(i + 1);

    return p;
}