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
struct ieee_modified_type {int dummy; } ;
struct ieee_handle {unsigned int modified_alloc; struct ieee_modified_type* modified; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct ieee_modified_type*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ xrealloc (struct ieee_modified_type*,unsigned int) ; 

__attribute__((used)) static struct ieee_modified_type *
ieee_get_modified_info (struct ieee_handle *info, unsigned int indx)
{
  if (indx >= info->modified_alloc)
    {
      unsigned int nalloc;

      nalloc = info->modified_alloc;
      if (nalloc == 0)
	nalloc = 16;
      while (indx >= nalloc)
	nalloc *= 2;
      info->modified = ((struct ieee_modified_type *)
			xrealloc (info->modified,
				  nalloc * sizeof *info->modified));
      memset (info->modified + info->modified_alloc, 0,
	      (nalloc - info->modified_alloc) * sizeof *info->modified);
      info->modified_alloc = nalloc;
    }

  return info->modified + indx;
}