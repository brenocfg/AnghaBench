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
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;

/* Variables and functions */
 int AV_PIX_FMT_RGB48BE ; 
 int AV_PIX_FMT_RGB48LE ; 
#define  AV_PIX_FMT_XYZ12BE 129 
#define  AV_PIX_FMT_XYZ12LE 128 

__attribute__((used)) static int handle_xyz(enum AVPixelFormat *format)
{
    switch (*format) {
    case AV_PIX_FMT_XYZ12BE : *format = AV_PIX_FMT_RGB48BE; return 1;
    case AV_PIX_FMT_XYZ12LE : *format = AV_PIX_FMT_RGB48LE; return 1;
    default:                                                return 0;
    }
}