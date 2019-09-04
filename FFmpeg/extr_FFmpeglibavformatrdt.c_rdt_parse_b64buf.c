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
 scalar_t__ AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  av_base64_decode (unsigned char*,char const*,unsigned int) ; 
 unsigned char* av_mallocz (scalar_t__) ; 
 int strlen (char const*) ; 

__attribute__((used)) static unsigned char *
rdt_parse_b64buf (unsigned int *target_len, const char *p)
{
    unsigned char *target;
    int len = strlen(p);
    if (*p == '\"') {
        p++;
        len -= 2; /* skip embracing " at start/end */
    }
    *target_len = len * 3 / 4;
    target = av_mallocz(*target_len + AV_INPUT_BUFFER_PADDING_SIZE);
    if (!target)
        return NULL;
    av_base64_decode(target, p, *target_len);
    return target;
}