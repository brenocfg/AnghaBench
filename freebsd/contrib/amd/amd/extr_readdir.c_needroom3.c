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
typedef  int /*<<< orphan*/  am_entry3 ;
typedef  int /*<<< orphan*/  am_dirlist3 ;

/* Variables and functions */

__attribute__((used)) static size_t needroom3(void)
{
  /*
   * Check for enough room.  This is extremely approximate but should
   * be enough space.  Really need 2 times:
   *      (8byte fileid
   *      8byte cookie
   *      8byte name pointer
   *      8byte next entry addres) = sizeof(am_entry3)
   *      2byte name + 1byte terminator
   * plus the size of the am_dirlist3 structure */
  return ((2 * ((sizeof(am_entry3) + sizeof("..") + 1))) + sizeof(am_dirlist3));
}