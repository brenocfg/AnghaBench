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
typedef  int /*<<< orphan*/  rawSeq ;
typedef  int /*<<< orphan*/  ZSTDMT_seqPool ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTDMT_setBufferSize (int /*<<< orphan*/ * const,size_t const) ; 

__attribute__((used)) static void ZSTDMT_setNbSeq(ZSTDMT_seqPool* const seqPool, size_t const nbSeq)
{
  ZSTDMT_setBufferSize(seqPool, nbSeq * sizeof(rawSeq));
}