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
typedef  int /*<<< orphan*/  b ;

/* Variables and functions */
 int /*<<< orphan*/  file ; 
 int /*<<< orphan*/  fwrite (char*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
wr_tr (void)
{
  /* The TR block is not normal - it doesn't have any contents.  */

  static char b[] =
    {
      0xff,			/* IT */
      0x03,			/* RL */
      0xfd,			/* CS */
    };
  fwrite (b, 1, sizeof (b), file);
}