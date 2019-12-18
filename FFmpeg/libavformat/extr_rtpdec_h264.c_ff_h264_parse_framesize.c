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
typedef  int /*<<< orphan*/  buf1 ;
struct TYPE_3__ {void* height; void* width; } ;
typedef  TYPE_1__ AVCodecParameters ;

/* Variables and functions */
 void* atoi (char const*) ; 

void ff_h264_parse_framesize(AVCodecParameters *par, const char *p)
{
    char buf1[50];
    char *dst = buf1;

    // remove the protocol identifier
    while (*p && *p == ' ')
        p++;                     // strip spaces.
    while (*p && *p != ' ')
        p++;                     // eat protocol identifier
    while (*p && *p == ' ')
        p++;                     // strip trailing spaces.
    while (*p && *p != '-' && (dst - buf1) < sizeof(buf1) - 1)
        *dst++ = *p++;
    *dst = '\0';

    // a='framesize:96 320-240'
    // set our parameters
    par->width   = atoi(buf1);
    par->height  = atoi(p + 1); // skip the -
}