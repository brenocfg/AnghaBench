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
struct bfd {int /*<<< orphan*/  where; } ;
typedef  int /*<<< orphan*/  file_ptr ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_NO_OPEN ; 
 int /*<<< orphan*/ * bfd_cache_lookup (struct bfd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  real_ftell (int /*<<< orphan*/ *) ; 

__attribute__((used)) static file_ptr
cache_btell (struct bfd *abfd)
{
  FILE *f = bfd_cache_lookup (abfd, CACHE_NO_OPEN);
  if (f == NULL)
    return abfd->where;
  return real_ftell (f);
}