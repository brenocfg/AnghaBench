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
struct cached_iconv {int dummy; } ;

/* Variables and functions */
 int cached_iconv_convert (struct cached_iconv*,int,int*) ; 

__attribute__((used)) static int
iconv_convert (void *baton, int from_char, int *to_char)
{
  struct cached_iconv *ci = baton;
  return cached_iconv_convert (ci, from_char, to_char);
}