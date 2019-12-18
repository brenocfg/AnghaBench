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
 int /*<<< orphan*/  SPOIL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memchr (void*,int,size_t) ; 

__attribute__((used)) static void xmemchr(void *dest, void *src, size_t n)
{
  /* Put the character at the end of the block */
  ((char *)src)[n-1] = 32;
  SPOIL(memchr(src, 32, n));
}