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
typedef  int bfd_boolean ;

/* Variables and functions */
 scalar_t__ memcmp (char const*,char const*,size_t) ; 
 size_t strcspn (char const*,char*) ; 

__attribute__((used)) static bfd_boolean
wild_spec_can_overlap (const char *name1, const char *name2)
{
  size_t prefix1_len = strcspn (name1, "?*[");
  size_t prefix2_len = strcspn (name2, "?*[");
  size_t min_prefix_len;

  /* Note that if there is no wildcard character, then we treat the
     terminating 0 as part of the prefix.  Thus ".text" won't match
     ".text." or ".text.*", for example.  */
  if (name1[prefix1_len] == '\0')
    prefix1_len++;
  if (name2[prefix2_len] == '\0')
    prefix2_len++;

  min_prefix_len = prefix1_len < prefix2_len ? prefix1_len : prefix2_len;

  return memcmp (name1, name2, min_prefix_len) == 0;
}