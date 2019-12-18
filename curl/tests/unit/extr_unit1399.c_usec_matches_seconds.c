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
typedef  int timediff_t ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int usec_magnitude ; 

__attribute__((used)) static bool usec_matches_seconds(timediff_t time_usec, int expected_seconds)
{
  int time_sec = (int)(time_usec / usec_magnitude);
  bool same = (time_sec == expected_seconds);
  fprintf(stderr, "is %d us same as %d seconds? %s\n",
          (int)time_usec, expected_seconds,
          same?"Yes":"No");
  return same;
}