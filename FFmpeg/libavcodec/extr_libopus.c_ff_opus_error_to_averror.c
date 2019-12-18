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

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AVERROR_UNKNOWN ; 
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENOSYS ; 
#define  OPUS_ALLOC_FAIL 134 
#define  OPUS_BAD_ARG 133 
#define  OPUS_BUFFER_TOO_SMALL 132 
#define  OPUS_INTERNAL_ERROR 131 
#define  OPUS_INVALID_PACKET 130 
#define  OPUS_INVALID_STATE 129 
#define  OPUS_UNIMPLEMENTED 128 

int ff_opus_error_to_averror(int err)
{
    switch (err) {
    case OPUS_BAD_ARG:
        return AVERROR(EINVAL);
    case OPUS_BUFFER_TOO_SMALL:
        return AVERROR_UNKNOWN;
    case OPUS_INTERNAL_ERROR:
        return AVERROR(EFAULT);
    case OPUS_INVALID_PACKET:
        return AVERROR_INVALIDDATA;
    case OPUS_UNIMPLEMENTED:
        return AVERROR(ENOSYS);
    case OPUS_INVALID_STATE:
        return AVERROR_UNKNOWN;
    case OPUS_ALLOC_FAIL:
        return AVERROR(ENOMEM);
    default:
        return AVERROR(EINVAL);
    }
}