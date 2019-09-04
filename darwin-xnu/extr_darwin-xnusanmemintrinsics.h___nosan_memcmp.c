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
 int memcmp (void const*,void const*,size_t) ; 

__attribute__((used)) static inline int   __nosan_memcmp(const void *a, const void *b, size_t sz) { return memcmp(a, b, sz); }