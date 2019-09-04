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
typedef  char uint8_t ;
typedef  int /*<<< orphan*/  GetByteContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  EINVAL ; 
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int bytestream2_get_be16 (int /*<<< orphan*/ *) ; 
 int bytestream2_get_buffer (int /*<<< orphan*/ *,char*,int) ; 

int ff_amf_get_string(GetByteContext *bc, uint8_t *str,
                      int strsize, int *length)
{
    int stringlen = 0;
    int readsize;
    stringlen = bytestream2_get_be16(bc);
    if (stringlen + 1 > strsize)
        return AVERROR(EINVAL);
    readsize = bytestream2_get_buffer(bc, str, stringlen);
    if (readsize != stringlen) {
        av_log(NULL, AV_LOG_WARNING,
               "Unable to read as many bytes as AMF string signaled\n");
    }
    str[readsize] = '\0';
    *length = FFMIN(stringlen, readsize);
    return 0;
}