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
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/ * file_desc ; 
 int /*<<< orphan*/ * ignore_initial ; 
 int /*<<< orphan*/  lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static off_t
file_position (int f)
{
  static bool positioned[2];
  static off_t position[2];

  if (! positioned[f])
    {
      positioned[f] = true;
      position[f] = lseek (file_desc[f], ignore_initial[f], SEEK_CUR);
    }
  return position[f];
}