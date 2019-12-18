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
 int /*<<< orphan*/  FPU_COPRO_NUMBER ; 
 int /*<<< orphan*/  MAX_REGISTER_SIZE ; 
 int /*<<< orphan*/  RDP_COPRO_READ ; 
 int RDP_FPU_READWRITE_MASK_FPS ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_rdp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  store_signed_integer (char*,int,int) ; 

__attribute__((used)) static void
rdp_fetch_one_fpu_register (int mask, char *buf)
{
#if 0
  /* !!! Since the PIE board doesn't work as documented,
     and it doesn't have FPU hardware anyway and since it
     slows everything down, I've disabled this. */
  int val;
  if (mask == RDP_FPU_READWRITE_MASK_FPS)
    {
      /* this guy is only a word */
      send_rdp ("bbw-SWZ", RDP_COPRO_READ, FPU_COPRO_NUMBER, mask, &val);
      store_signed_integer (buf, 4, val);
    }
  else
    {
      /* There are 12 bytes long 
         !! fixme about endianness 
       */
      int dummy;		/* I've seen these come back as four words !! */
      send_rdp ("bbw-SWWWWZ", RDP_COPRO_READ, FPU_COPRO_NUMBER, mask, buf + 0, buf + 4, buf + 8, &dummy);
    }
#endif
  memset (buf, 0, MAX_REGISTER_SIZE);
}