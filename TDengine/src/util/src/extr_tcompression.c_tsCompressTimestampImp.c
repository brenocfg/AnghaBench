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
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int int64_t ;

/* Variables and functions */
 int BITS_PER_BYTE ; 
 int BUILDIN_CLZL (int) ; 
 int CHAR_BYTES ; 
 int LONG_BYTES ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ is_bigendian () ; 
 int /*<<< orphan*/  memcpy (char* const,...) ; 
 int /*<<< orphan*/  safeInt64Add (int,int) ; 

int tsCompressTimestampImp(const char *const input, const int nelements, char *const output) {
  int _pos = 1;
  assert(nelements >= 0);

  if (nelements == 0) return 0;

  int64_t *istream = (int64_t *)input;

  int64_t  prev_value = istream[0];
  int64_t  prev_delta = -prev_value;
  uint8_t  flags = 0, flag1 = 0, flag2 = 0;
  uint64_t dd1 = 0, dd2 = 0;

  for (int i = 0; i < nelements; i++) {
    int64_t curr_value = istream[i];
    if (!safeInt64Add(curr_value, -prev_value)) goto _exit_over;
    int64_t curr_delta = curr_value - prev_value;
    if (!safeInt64Add(curr_delta, -prev_delta)) goto _exit_over;
    int64_t delta_of_delta = curr_delta - prev_delta;
    // zigzag encode the value.
    uint64_t zigzag_value = (delta_of_delta >> (LONG_BYTES * BITS_PER_BYTE - 1)) ^ (delta_of_delta << 1);
    if (i % 2 == 0) {
      flags = 0;
      dd1 = zigzag_value;
      if (dd1 == 0) {
        flag1 = 0;
      } else {
        flag1 = LONG_BYTES - BUILDIN_CLZL(dd1) / BITS_PER_BYTE;
      }
    } else {
      dd2 = zigzag_value;
      if (dd2 == 0) {
        flag2 = 0;
      } else {
        flag2 = LONG_BYTES - BUILDIN_CLZL(dd2) / BITS_PER_BYTE;
      }
      flags = flag1 | (flag2 << 4);
      // Encode the flag.
      if ((_pos + CHAR_BYTES - 1) >= nelements * LONG_BYTES) goto _exit_over;
      memcpy(output + _pos, &flags, CHAR_BYTES);
      _pos += CHAR_BYTES;
      /* Here, we assume it is little endian encoding method. */
      // Encode dd1
      if (is_bigendian()) {
        if ((_pos + flag1 - 1) >= nelements * LONG_BYTES) goto _exit_over;
        memcpy(output + _pos, (char *)(&dd1) + LONG_BYTES - flag1, flag1);
      } else {
        if ((_pos + flag1 - 1) >= nelements * LONG_BYTES) goto _exit_over;
        memcpy(output + _pos, (char *)(&dd1), flag1);
      }
      _pos += flag1;
      // Encode dd2;
      if (is_bigendian()) {
        if ((_pos + flag2 - 1) >= nelements * LONG_BYTES) goto _exit_over;
        memcpy(output + _pos, (char *)(&dd2) + LONG_BYTES - flag2, flag2);
      } else {
        if ((_pos + flag2 - 1) >= nelements * LONG_BYTES) goto _exit_over;
        memcpy(output + _pos, (char *)(&dd2), flag2);
      }
      _pos += flag2;
    }
    prev_value = curr_value;
    prev_delta = curr_delta;
  }

  if (nelements % 2 == 1) {
    flag2 = 0;
    flags = flag1 | (flag2 << 4);
    // Encode the flag.
    if ((_pos + CHAR_BYTES - 1) >= nelements * LONG_BYTES) goto _exit_over;
    memcpy(output + _pos, &flags, CHAR_BYTES);
    _pos += CHAR_BYTES;
    // Encode dd1;
    if (is_bigendian()) {
      if ((_pos + flag1 - 1) >= nelements * LONG_BYTES) goto _exit_over;
      memcpy(output + _pos, (char *)(&dd1) + LONG_BYTES - flag1, flag1);
    } else {
      if ((_pos + flag1 - 1) >= nelements * LONG_BYTES) goto _exit_over;
      memcpy(output + _pos, (char *)(&dd1), flag1);
    }
    _pos += flag1;
  }

  output[0] = 1;  // Means the string is compressed
  return _pos;

_exit_over:
  output[0] = 0;  // Means the string is not compressed
  memcpy(output + 1, input, nelements * LONG_BYTES);
  return nelements * LONG_BYTES + 1;
}