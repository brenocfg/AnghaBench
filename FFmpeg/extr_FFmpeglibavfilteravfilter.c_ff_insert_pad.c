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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/ * AVFilterPad ;
typedef  int /*<<< orphan*/  AVFilterLink ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 unsigned int FFMIN (unsigned int,unsigned int) ; 
 int /*<<< orphan*/ ** av_realloc_array (int /*<<< orphan*/ **,unsigned int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 

int ff_insert_pad(unsigned idx, unsigned *count, size_t padidx_off,
                   AVFilterPad **pads, AVFilterLink ***links,
                   AVFilterPad *newpad)
{
    AVFilterLink **newlinks;
    AVFilterPad *newpads;
    unsigned i;

    idx = FFMIN(idx, *count);

    newpads  = av_realloc_array(*pads,  *count + 1, sizeof(AVFilterPad));
    newlinks = av_realloc_array(*links, *count + 1, sizeof(AVFilterLink*));
    if (newpads)
        *pads  = newpads;
    if (newlinks)
        *links = newlinks;
    if (!newpads || !newlinks)
        return AVERROR(ENOMEM);

    memmove(*pads  + idx + 1, *pads  + idx, sizeof(AVFilterPad)   * (*count - idx));
    memmove(*links + idx + 1, *links + idx, sizeof(AVFilterLink*) * (*count - idx));
    memcpy(*pads + idx, newpad, sizeof(AVFilterPad));
    (*links)[idx] = NULL;

    (*count)++;
    for (i = idx + 1; i < *count; i++)
        if ((*links)[i])
            (*(unsigned *)((uint8_t *) (*links)[i] + padidx_off))++;

    return 0;
}