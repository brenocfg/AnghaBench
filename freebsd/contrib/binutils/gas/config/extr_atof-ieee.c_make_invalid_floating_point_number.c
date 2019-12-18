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
typedef  int LITTLENUM_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
make_invalid_floating_point_number (LITTLENUM_TYPE *words)
{
  as_bad (_("cannot create floating-point number"));
  /* Zero the leftmost bit.  */
  words[0] = (LITTLENUM_TYPE) ((unsigned) -1) >> 1;
  words[1] = (LITTLENUM_TYPE) -1;
  words[2] = (LITTLENUM_TYPE) -1;
  words[3] = (LITTLENUM_TYPE) -1;
  words[4] = (LITTLENUM_TYPE) -1;
  words[5] = (LITTLENUM_TYPE) -1;
}