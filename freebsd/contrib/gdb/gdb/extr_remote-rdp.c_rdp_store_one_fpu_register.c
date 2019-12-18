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
 int /*<<< orphan*/  RDP_COPRO_WRITE ; 
 int RDP_FPU_READWRITE_MASK_FPS ; 
 int extract_unsigned_integer (char*,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  send_rdp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,...) ; 

__attribute__((used)) static void
rdp_store_one_fpu_register (int mask, char *buf)
{
#if 0
  /* See comment in fetch_one_fpu_register */
  if (mask == RDP_FPU_READWRITE_MASK_FPS)
    {
      int val = extract_unsigned_integer (buf, 4);
      /* this guy is only a word */
      send_rdp ("bbww-SZ", RDP_COPRO_WRITE,
		FPU_COPRO_NUMBER,
		mask, val);
    }
  else
    {
      /* There are 12 bytes long 
         !! fixme about endianness 
       */
      int dummy = 0;
      /* I've seen these come as four words, not the three advertized !! */
      printf ("Sending mask %x\n", mask);
      send_rdp ("bbwwwww-SZ",
		RDP_COPRO_WRITE,
		FPU_COPRO_NUMBER,
		mask,
		*(int *) (buf + 0),
		*(int *) (buf + 4),
		*(int *) (buf + 8),
		0);

      printf ("done mask %x\n", mask);
    }
#endif
}