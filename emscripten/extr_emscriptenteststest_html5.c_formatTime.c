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
 int /*<<< orphan*/  sprintf (char*,char*,int,int,...) ; 

void formatTime(char *str, int seconds)
{
  int h = seconds / (60*60);
  seconds -= h*60*60;
  int m = seconds / 60;
  seconds -= m*60;
  if (h > 0)
  {
    sprintf(str, "%dh:%02dm:%02ds", h, m, seconds);
  }
  else
  {
    sprintf(str, "%02dm:%02ds", m, seconds);
  }
}