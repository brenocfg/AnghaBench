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
typedef  scalar_t__ char_class ;

/* Variables and functions */
 scalar_t__ ISALNUM (unsigned char) ; 
 scalar_t__ charclass (unsigned char) ; 

__attribute__((used)) static void setcharorrange(unsigned char **pp, unsigned char *charset)
{
  unsigned char *p = (*pp)++;
  unsigned char c = *p++;

  charset[c] = 1;
  if(ISALNUM(c) && *p++ == '-') {
    char_class cc = charclass(c);
    unsigned char endrange = *p++;

    if(endrange == '\\')
      endrange = *p++;
    if(endrange >= c && charclass(endrange) == cc) {
      while(c++ != endrange)
        if(charclass(c) == cc)  /* Chars in class may be not consecutive. */
          charset[c] = 1;
      *pp = p;
    }
  }
}