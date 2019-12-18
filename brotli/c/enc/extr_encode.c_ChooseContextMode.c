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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {scalar_t__ quality; } ;
typedef  int /*<<< orphan*/  ContextType ;
typedef  TYPE_1__ BrotliEncoderParams ;

/* Variables and functions */
 int /*<<< orphan*/  BrotliIsMostlyUTF8 (int /*<<< orphan*/  const*,size_t const,size_t const,size_t const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONTEXT_SIGNED ; 
 int /*<<< orphan*/  CONTEXT_UTF8 ; 
 scalar_t__ MIN_QUALITY_FOR_HQ_BLOCK_SPLITTING ; 
 int /*<<< orphan*/  kMinUTF8Ratio ; 

__attribute__((used)) static ContextType ChooseContextMode(const BrotliEncoderParams* params,
    const uint8_t* data, const size_t pos, const size_t mask,
    const size_t length) {
  /* We only do the computation for the option of something else than
     CONTEXT_UTF8 for the highest qualities */
  if (params->quality >= MIN_QUALITY_FOR_HQ_BLOCK_SPLITTING &&
      !BrotliIsMostlyUTF8(data, pos, mask, length, kMinUTF8Ratio)) {
    return CONTEXT_SIGNED;
  }
  return CONTEXT_UTF8;
}