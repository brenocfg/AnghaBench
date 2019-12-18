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
#define  FF_QSCALE_TYPE_H264 131 
#define  FF_QSCALE_TYPE_MPEG1 130 
#define  FF_QSCALE_TYPE_MPEG2 129 
#define  FF_QSCALE_TYPE_VP56 128 

__attribute__((used)) static inline int ff_norm_qscale(int qscale, int type)
{
    switch (type) {
    case FF_QSCALE_TYPE_MPEG1: return qscale;
    case FF_QSCALE_TYPE_MPEG2: return qscale >> 1;
    case FF_QSCALE_TYPE_H264:  return qscale >> 2;
    case FF_QSCALE_TYPE_VP56:  return (63 - qscale + 2) >> 2;
    }
    return qscale;
}