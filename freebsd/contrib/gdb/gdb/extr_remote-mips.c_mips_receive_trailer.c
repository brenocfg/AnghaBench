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
 int SERIAL_TIMEOUT ; 
 int /*<<< orphan*/  TRLR_CHECK (int) ; 
 int TRLR_LENGTH ; 
 int mips_readchar (int) ; 

__attribute__((used)) static int
mips_receive_trailer (unsigned char *trlr, int *pgarbage, int *pch, int timeout)
{
  int i;
  int ch;

  for (i = 0; i < TRLR_LENGTH; i++)
    {
      ch = mips_readchar (timeout);
      *pch = ch;
      if (ch == SERIAL_TIMEOUT)
	return -1;
      if (!TRLR_CHECK (ch))
	return -2;
      trlr[i] = ch;
    }
  return 0;
}