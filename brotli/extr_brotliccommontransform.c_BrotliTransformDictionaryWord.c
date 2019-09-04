#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_6__ {unsigned int* params; } ;
typedef  TYPE_1__ BrotliTransforms ;

/* Variables and functions */
 int const BROTLI_TRANSFORM_OMIT_FIRST_1 ; 
 int const BROTLI_TRANSFORM_OMIT_FIRST_9 ; 
 int const BROTLI_TRANSFORM_OMIT_LAST_9 ; 
 int* BROTLI_TRANSFORM_PREFIX (TYPE_1__ const*,int) ; 
 int const BROTLI_TRANSFORM_SHIFT_ALL ; 
 int const BROTLI_TRANSFORM_SHIFT_FIRST ; 
 int* BROTLI_TRANSFORM_SUFFIX (TYPE_1__ const*,int) ; 
 int BROTLI_TRANSFORM_TYPE (TYPE_1__ const*,int) ; 
 int const BROTLI_TRANSFORM_UPPERCASE_ALL ; 
 int const BROTLI_TRANSFORM_UPPERCASE_FIRST ; 
 int Shift (int*,int,int /*<<< orphan*/ ) ; 
 int ToUpperCase (int*) ; 

int BrotliTransformDictionaryWord(uint8_t* dst, const uint8_t* word, int len,
    const BrotliTransforms* transforms, int transform_idx) {
  int idx = 0;
  const uint8_t* prefix = BROTLI_TRANSFORM_PREFIX(transforms, transform_idx);
  uint8_t type = BROTLI_TRANSFORM_TYPE(transforms, transform_idx);
  const uint8_t* suffix = BROTLI_TRANSFORM_SUFFIX(transforms, transform_idx);
  {
    int prefix_len = *prefix++;
    while (prefix_len--) { dst[idx++] = *prefix++; }
  }
  {
    const int t = type;
    int i = 0;
    if (t <= BROTLI_TRANSFORM_OMIT_LAST_9) {
      len -= t;
    } else if (t >= BROTLI_TRANSFORM_OMIT_FIRST_1
        && t <= BROTLI_TRANSFORM_OMIT_FIRST_9) {
      int skip = t - (BROTLI_TRANSFORM_OMIT_FIRST_1 - 1);
      word += skip;
      len -= skip;
    }
    while (i < len) { dst[idx++] = word[i++]; }
    if (t == BROTLI_TRANSFORM_UPPERCASE_FIRST) {
      ToUpperCase(&dst[idx - len]);
    } else if (t == BROTLI_TRANSFORM_UPPERCASE_ALL) {
      uint8_t* uppercase = &dst[idx - len];
      while (len > 0) {
        int step = ToUpperCase(uppercase);
        uppercase += step;
        len -= step;
      }
    } else if (t == BROTLI_TRANSFORM_SHIFT_FIRST) {
      uint16_t param = (uint16_t)(transforms->params[transform_idx * 2]
          + (transforms->params[transform_idx * 2 + 1] << 8u));
      Shift(&dst[idx - len], len, param);
    } else if (t == BROTLI_TRANSFORM_SHIFT_ALL) {
      uint16_t param = (uint16_t)(transforms->params[transform_idx * 2]
          + (transforms->params[transform_idx * 2 + 1] << 8u));
      uint8_t* shift = &dst[idx - len];
      while (len > 0) {
        int step = Shift(shift, len, param);
        shift += step;
        len -= step;
      }
    }
  }
  {
    int suffix_len = *suffix++;
    while (suffix_len--) { dst[idx++] = *suffix++; }
    return idx;
  }
}