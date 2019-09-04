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
typedef  int /*<<< orphan*/  AVCodecDescriptor ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* codec_descriptors ; 

const AVCodecDescriptor *avcodec_descriptor_next(const AVCodecDescriptor *prev)
{
    if (!prev)
        return &codec_descriptors[0];
    if (prev - codec_descriptors < FF_ARRAY_ELEMS(codec_descriptors) - 1)
        return prev + 1;
    return NULL;
}