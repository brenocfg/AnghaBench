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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 scalar_t__ BINFO_BASE_ITERATE (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BINFO_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_ATTRIBUTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_BINFO (int /*<<< orphan*/ ) ; 
 scalar_t__ lookup_attribute (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
typeinfo_comdat (tree type)
{
  tree binfo, base_binfo;
  int j;

  if (lookup_attribute ("weak", TYPE_ATTRIBUTES (type)))
    return true;
  
  for (binfo = TYPE_BINFO (type), j = 0;
	BINFO_BASE_ITERATE (binfo, j, base_binfo); ++j)
    {
      if (typeinfo_comdat (BINFO_TYPE (base_binfo)))
	return true;
    }

  return false;
}