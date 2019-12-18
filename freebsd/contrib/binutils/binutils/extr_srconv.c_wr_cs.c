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
wr_cs (void)
{
  /* It seems that the CS struct is not normal - the size is wrong
     heres one I prepared earlier.  */
  static char b[] =
    {
    0x80,			/* IT */
    0x21,			/* RL */
    0x00,			/* number of chars in variable length part */
    0x80,			/* hd */
    0x00,			/* hs */
    0x80,			/* un */
    0x00,			/* us */
    0x80,			/* sc */
    0x00,			/* ss */
    0x80,			/* er */
    0x80,			/* ed */
    0x80,			/* sh */
    0x80,			/* ob */
    0x80,			/* rl */
    0x80,			/* du */
    0x80,			/* dps */
    0x80,			/* dsy */
    0x80,			/* dty */
    0x80,			/* dln */
    0x80,			/* dso */
    0x80,			/* dus */
    0x00,			/* dss */
    0x80,			/* dbt */
    0x00,			/* dpp */
    0x80,			/* dfp */
    0x80,			/* den */
    0x80,			/* dds */
    0x80,			/* dar */
    0x80,			/* dpt */
    0x00,			/* dul */
    0x00,			/* dse */
    0x00,			/* dot */
    0xDE			/* CS */
  };
  fwrite (b, 1, sizeof (b), file);
}