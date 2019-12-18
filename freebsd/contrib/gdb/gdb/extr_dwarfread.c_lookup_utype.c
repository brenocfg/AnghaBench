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
struct type {int dummy; } ;
typedef  int DIE_REF ;

/* Variables and functions */
 int /*<<< orphan*/  DIE_ID ; 
 int /*<<< orphan*/  DIE_NAME ; 
 int /*<<< orphan*/  bad_die_ref_complaint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int dbroff ; 
 int numutypes ; 
 struct type** utypes ; 

__attribute__((used)) static struct type *
lookup_utype (DIE_REF die_ref)
{
  struct type *type = NULL;
  int utypeidx;

  utypeidx = (die_ref - dbroff) / 4;
  if ((utypeidx < 0) || (utypeidx >= numutypes))
    {
      bad_die_ref_complaint (DIE_ID, DIE_NAME, die_ref);
    }
  else
    {
      type = *(utypes + utypeidx);
    }
  return (type);
}