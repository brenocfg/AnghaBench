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
typedef  int /*<<< orphan*/  rawSeqStore_t ;
struct TYPE_4__ {scalar_t__ bufferSize; } ;
typedef  TYPE_1__ ZSTDMT_seqPool ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTDMT_getBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  bufferToSeq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kNullRawSeqStore ; 

__attribute__((used)) static rawSeqStore_t ZSTDMT_getSeq(ZSTDMT_seqPool* seqPool)
{
    if (seqPool->bufferSize == 0) {
        return kNullRawSeqStore;
    }
    return bufferToSeq(ZSTDMT_getBuffer(seqPool));
}