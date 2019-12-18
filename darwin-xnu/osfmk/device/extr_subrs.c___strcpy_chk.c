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

/* Variables and functions */
 scalar_t__ __improbable (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  panic (char*,char*,char const*,size_t,size_t) ; 
 size_t strlen (char const*) ; 

char *
__strcpy_chk (char *restrict dst, const char *restrict src, size_t chk_size)
{
  size_t len = strlen(src);
  if (__improbable (chk_size < len + 1)) {
    panic("__strcpy_chk object size check failed: dst %p, src %p, (%zu < %zu + 1)", dst, src, chk_size, len);
  }
  memcpy(dst, src, len+1);
  return dst;
}