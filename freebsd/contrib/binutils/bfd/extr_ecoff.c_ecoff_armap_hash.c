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
 unsigned int ARMAP_HASH_MAGIC ; 

__attribute__((used)) static unsigned int
ecoff_armap_hash (const char *s,
		  unsigned int *rehash,
		  unsigned int size,
		  unsigned int hlog)
{
  unsigned int hash;

  if (hlog == 0)
    return 0;
  hash = *s++;
  while (*s != '\0')
    hash = ((hash >> 27) | (hash << 5)) + *s++;
  hash *= ARMAP_HASH_MAGIC;
  *rehash = (hash & (size - 1)) | 1;
  return hash >> (32 - hlog);
}