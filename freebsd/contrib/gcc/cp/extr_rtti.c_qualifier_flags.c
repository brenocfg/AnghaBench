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
 int TYPE_QUAL_CONST ; 
 int TYPE_QUAL_RESTRICT ; 
 int TYPE_QUAL_VOLATILE ; 
 int cp_type_quals (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qualifier_flags (tree type)
{
  int flags = 0;
  int quals = cp_type_quals (type);

  if (quals & TYPE_QUAL_CONST)
    flags |= 1;
  if (quals & TYPE_QUAL_VOLATILE)
    flags |= 2;
  if (quals & TYPE_QUAL_RESTRICT)
    flags |= 4;
  return flags;
}