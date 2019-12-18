#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ byteorder; scalar_t__ flavour; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ bfd_target ;
struct TYPE_6__ {scalar_t__ endian; } ;

/* Variables and functions */
 scalar_t__ BFD_ENDIAN_BIG ; 
 scalar_t__ BFD_ENDIAN_LITTLE ; 
 scalar_t__ ENDIAN_BIG ; 
 scalar_t__ ENDIAN_LITTLE ; 
 TYPE_3__ command_line ; 
 scalar_t__ name_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ const* winner ; 

__attribute__((used)) static int
closest_target_match (const bfd_target *target, void *data)
{
  const bfd_target *original = data;

  if (command_line.endian == ENDIAN_BIG
      && target->byteorder != BFD_ENDIAN_BIG)
    return 0;

  if (command_line.endian == ENDIAN_LITTLE
      && target->byteorder != BFD_ENDIAN_LITTLE)
    return 0;

  /* Must be the same flavour.  */
  if (target->flavour != original->flavour)
    return 0;

  /* If we have not found a potential winner yet, then record this one.  */
  if (winner == NULL)
    {
      winner = target;
      return 0;
    }

  /* Oh dear, we now have two potential candidates for a successful match.
     Compare their names and choose the better one.  */
  if (name_compare (target->name, original->name)
      > name_compare (winner->name, original->name))
    winner = target;

  /* Keep on searching until wqe have checked them all.  */
  return 0;
}