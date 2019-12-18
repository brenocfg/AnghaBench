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
struct TYPE_3__ {int buf_size; char* buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_EXTENSION ; 
 int AVPROBE_SCORE_MAX ; 
 int AV_RL16 (char*) ; 
 int MTV_HEADER_SIZE ; 
 char MTV_IMAGE_DEFAULT_BPP ; 

__attribute__((used)) static int mtv_probe(const AVProbeData *p)
{
    /* we need at least 57 bytes from the header
     * to try parsing all required fields
     */
    if (p->buf_size < 57)
        return 0;

    /* Magic is 'AMV' */
    if (*p->buf != 'A' || *(p->buf + 1) != 'M' || *(p->buf + 2) != 'V')
        return 0;

    /* Audio magic is always MP3 */
    if (p->buf[43] != 'M' || p->buf[44] != 'P' || p->buf[45] != '3')
        return 0;

    /* Check for nonzero in bpp and (width|height) header fields */
    if(!(p->buf[51] && AV_RL16(&p->buf[52]) | AV_RL16(&p->buf[54])))
        return 0;

    /* If width or height are 0 then imagesize header field should not */
    if(!AV_RL16(&p->buf[52]) || !AV_RL16(&p->buf[54]))
    {
        if(!!AV_RL16(&p->buf[56]))
            return AVPROBE_SCORE_EXTENSION;
        else
            return 0;
    }

    /* Image bpp is not an absolutely required
     * field as we latter claim it should be 16
     * no matter what. All samples in the wild
     * are RGB565/555.
     */
    if(p->buf[51] != MTV_IMAGE_DEFAULT_BPP)
        return AVPROBE_SCORE_EXTENSION / 2;

    /* We had enough data to parse header values
     * but we expect to be able to get 512 bytes
     * of header to be sure.
     */
    if (p->buf_size < MTV_HEADER_SIZE)
        return AVPROBE_SCORE_EXTENSION;

    return AVPROBE_SCORE_MAX;
}