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
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  mips_error (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_receive_wait ; 
 unsigned int mips_request (char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  paddr_nz (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
mips_fetch_word (CORE_ADDR addr)
{
  unsigned int val;
  int err;

  val = mips_request ('d', addr, 0, &err, mips_receive_wait, NULL);
  if (err)
    {
      /* Data space failed; try instruction space.  */
      val = mips_request ('i', addr, 0, &err,
			  mips_receive_wait, NULL);
      if (err)
	mips_error ("Can't read address 0x%s: %s",
		    paddr_nz (addr), safe_strerror (errno));
    }
  return val;
}