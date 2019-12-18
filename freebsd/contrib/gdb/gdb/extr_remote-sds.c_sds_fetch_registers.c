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
 size_t DEPRECATED_REGISTER_BYTE (int) ; 
 int /*<<< orphan*/  DEPRECATED_REGISTER_BYTES ; 
 int NUM_REGS ; 
 int PBUFSIZ ; 
 char* alloca (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sds_send (unsigned char*,int) ; 
 unsigned char* sprs ; 
 int /*<<< orphan*/  supply_register (int,char*) ; 

__attribute__((used)) static void
sds_fetch_registers (int regno)
{
  unsigned char buf[PBUFSIZ];
  int i, retlen;
  char *regs = alloca (DEPRECATED_REGISTER_BYTES);

  /* Unimplemented registers read as all bits zero.  */
  memset (regs, 0, DEPRECATED_REGISTER_BYTES);

  buf[0] = 18;
  buf[1] = 1;
  buf[2] = 0;
  retlen = sds_send (buf, 3);

  for (i = 0; i < 4 * 6; ++i)
    regs[i + 4 * 32 + 8 * 32] = buf[i];
  for (i = 0; i < 4 * 4; ++i)
    sprs[i] = buf[i + 4 * 7];

  buf[0] = 18;
  buf[1] = 2;
  buf[2] = 0;
  retlen = sds_send (buf, 3);

  for (i = 0; i < retlen; i++)
    regs[i] = buf[i];

  /* (should warn about reply too short) */

  for (i = 0; i < NUM_REGS; i++)
    supply_register (i, &regs[DEPRECATED_REGISTER_BYTE (i)]);
}