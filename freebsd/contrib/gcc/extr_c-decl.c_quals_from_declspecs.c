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
struct c_declspecs {scalar_t__ typespec_word; scalar_t__ storage_class; int /*<<< orphan*/  thread_p; int /*<<< orphan*/  inline_p; int /*<<< orphan*/  complex_p; int /*<<< orphan*/  unsigned_p; int /*<<< orphan*/  signed_p; int /*<<< orphan*/  short_p; int /*<<< orphan*/  long_long_p; int /*<<< orphan*/  long_p; int /*<<< orphan*/  deprecated_p; int /*<<< orphan*/  explicit_signed_p; int /*<<< orphan*/  typedef_p; int /*<<< orphan*/  decl_attr; int /*<<< orphan*/  type; scalar_t__ restrict_p; scalar_t__ volatile_p; scalar_t__ const_p; } ;

/* Variables and functions */
 int TYPE_QUAL_CONST ; 
 int TYPE_QUAL_RESTRICT ; 
 int TYPE_QUAL_VOLATILE ; 
 scalar_t__ csc_none ; 
 scalar_t__ cts_none ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

int
quals_from_declspecs (const struct c_declspecs *specs)
{
  int quals = ((specs->const_p ? TYPE_QUAL_CONST : 0)
	       | (specs->volatile_p ? TYPE_QUAL_VOLATILE : 0)
	       | (specs->restrict_p ? TYPE_QUAL_RESTRICT : 0));
  gcc_assert (!specs->type
	      && !specs->decl_attr
	      && specs->typespec_word == cts_none
	      && specs->storage_class == csc_none
	      && !specs->typedef_p
	      && !specs->explicit_signed_p
	      && !specs->deprecated_p
	      && !specs->long_p
	      && !specs->long_long_p
	      && !specs->short_p
	      && !specs->signed_p
	      && !specs->unsigned_p
	      && !specs->complex_p
	      && !specs->inline_p
	      && !specs->thread_p);
  return quals;
}