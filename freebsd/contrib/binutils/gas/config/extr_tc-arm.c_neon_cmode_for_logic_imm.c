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
 int FAIL ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  first_error (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
neon_cmode_for_logic_imm (unsigned immediate, unsigned *immbits, int size)
{
  /* Handle .I8 pseudo-instructions.  */
  if (size == 8)
    {
      /* Unfortunately, this will make everything apart from zero out-of-range.
         FIXME is this the intended semantics? There doesn't seem much point in
         accepting .I8 if so.  */
      immediate |= immediate << 8;
      size = 16;
    }

  if (size >= 32)
    {
      if (immediate == (immediate & 0x000000ff))
	{
	  *immbits = immediate;
	  return 0x1;
	}
      else if (immediate == (immediate & 0x0000ff00))
	{
	  *immbits = immediate >> 8;
	  return 0x3;
	}
      else if (immediate == (immediate & 0x00ff0000))
	{
	  *immbits = immediate >> 16;
	  return 0x5;
	}
      else if (immediate == (immediate & 0xff000000))
	{
	  *immbits = immediate >> 24;
	  return 0x7;
	}
      if ((immediate & 0xffff) != (immediate >> 16))
	goto bad_immediate;
      immediate &= 0xffff;
    }

  if (immediate == (immediate & 0x000000ff))
    {
      *immbits = immediate;
      return 0x9;
    }
  else if (immediate == (immediate & 0x0000ff00))
    {
      *immbits = immediate >> 8;
      return 0xb;
    }

  bad_immediate:
  first_error (_("immediate value out of range"));
  return FAIL;
}