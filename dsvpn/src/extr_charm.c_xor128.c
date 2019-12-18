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
typedef  int /*<<< orphan*/  __m128i ;

/* Variables and functions */
 int /*<<< orphan*/  _mm_loadu_si128 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  _mm_storeu_si128 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_xor_si128 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void xor128(void *out, const void *in)
{
#ifdef __SSSE3__
    _mm_storeu_si128((__m128i *) out,
                     _mm_xor_si128(_mm_loadu_si128((const __m128i *) out),
                                   _mm_loadu_si128((const __m128i *) in)));
#else
    unsigned char *      out_ = (unsigned char *) out;
    const unsigned char *in_  = (const unsigned char *) in;
    size_t               i;

    for (i = 0; i < 16; i++) {
        out_[i] ^= in_[i];
    }
#endif
}