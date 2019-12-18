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
 int strspn (char const*,char const*) ; 

__attribute__((used)) static const char *span (const void *ud, const char *o,
                                         const char *s,
                                         const char *e) {
  const char *u = (const char *)ud;
  (void)o; (void)e;
  return s + strspn(s, u);
}