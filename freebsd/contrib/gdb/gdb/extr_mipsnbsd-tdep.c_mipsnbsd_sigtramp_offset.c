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
typedef  int /*<<< orphan*/  w ;
typedef  int /*<<< orphan*/  ret ;
typedef  int LONGEST ;
typedef  int CORE_ADDR ;

/* Variables and functions */
 scalar_t__ BFD_ENDIAN_BIG ; 
 int RETCODE_NWORDS ; 
 int RETCODE_SIZE ; 
 scalar_t__ TARGET_BYTE_ORDER ; 
 scalar_t__ memcmp (unsigned char*,char const*,int) ; 
 scalar_t__ read_memory_nobpt (int,char*,int) ; 
 char* sigtramp_retcode_mipseb ; 
 char* sigtramp_retcode_mipsel ; 

__attribute__((used)) static LONGEST
mipsnbsd_sigtramp_offset (CORE_ADDR pc)
{
  const char *retcode = TARGET_BYTE_ORDER == BFD_ENDIAN_BIG
  	? sigtramp_retcode_mipseb : sigtramp_retcode_mipsel;
  unsigned char ret[RETCODE_SIZE], w[4];
  LONGEST off;
  int i;

  if (read_memory_nobpt (pc, (char *) w, sizeof (w)) != 0)
    return -1;

  for (i = 0; i < RETCODE_NWORDS; i++)
    {
      if (memcmp (w, retcode + (i * 4), 4) == 0)
	break;
    }
  if (i == RETCODE_NWORDS)
    return -1;

  off = i * 4;
  pc -= off;

  if (read_memory_nobpt (pc, (char *) ret, sizeof (ret)) != 0)
    return -1;

  if (memcmp (ret, retcode, RETCODE_SIZE) == 0)
    return off;

  return -1;
}