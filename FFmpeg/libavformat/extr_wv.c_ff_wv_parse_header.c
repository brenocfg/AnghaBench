#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int blocksize; int flags; int initial; int final; scalar_t__ crc; scalar_t__ samples; scalar_t__ block_idx; scalar_t__ total_samples; int /*<<< orphan*/  version; } ;
typedef  TYPE_1__ WvHeader ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_RL16 (int /*<<< orphan*/  const*) ; 
 scalar_t__ AV_RL32 (int /*<<< orphan*/  const*) ; 
 scalar_t__ MKTAG (char,char,char,char) ; 
 int WV_BLOCK_LIMIT ; 
 int WV_FLAG_FINAL_BLOCK ; 
 int WV_FLAG_INITIAL_BLOCK ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

int ff_wv_parse_header(WvHeader *wv, const uint8_t *data)
{
    memset(wv, 0, sizeof(*wv));

    if (AV_RL32(data) != MKTAG('w', 'v', 'p', 'k'))
        return AVERROR_INVALIDDATA;

    wv->blocksize     = AV_RL32(data + 4);
    if (wv->blocksize < 24 || wv->blocksize > WV_BLOCK_LIMIT)
        return AVERROR_INVALIDDATA;
    wv->blocksize -= 24;

    wv->version       = AV_RL16(data + 8);
    wv->total_samples = AV_RL32(data + 12);
    wv->block_idx     = AV_RL32(data + 16);
    wv->samples       = AV_RL32(data + 20);
    wv->flags         = AV_RL32(data + 24);
    wv->crc           = AV_RL32(data + 28);

    wv->initial = !!(wv->flags & WV_FLAG_INITIAL_BLOCK);
    wv->final   = !!(wv->flags & WV_FLAG_FINAL_BLOCK);

    return 0;
}